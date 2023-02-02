#include <chrono>
#include <cmath>

#include <frc/SmartDashboard/SmartDashboard.h>

#include <frc2/command/CommandScheduler.h>

#include "Robot.hpp"

void Robot::RobotInit() {
  // nothing
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit() {
  drive.stop_power();

  // NEVER REMOVE THIS:
  launch.stop();
}

void Robot::DisabledPeriodic() {
  // nothing
}

void Robot::AutonomousInit() {
  // nothing
}

void Robot::AutonomousPeriodic() {
  // nothing
}

void Robot::TeleopInit() {
  drive.configure_motors();

  // NEVER REMOVE THIS:
  launch.stop();
}

void Robot::TeleopPeriodic() {
  if (controller.GetAButton()) {
    launch.launch();
  }

  auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  );

  if ((now - launch.launch_start_time) > launch.LAUNCH_LENGTH) {
    launch.stop();
  }

  if (controller.GetAButtonReleased()) {
    launch.enable_launch();
  }

  if (controller.GetBButtonReleased()) {
    drive.reset_pid();
  }

  if (controller.GetXButtonReleased()) {
    drive.toggle_auto_balance();
  }

  double pitch = imu.GetXFilteredAccelAngle().value();

  if (pitch > 180) {
    pitch -= 360;
  }

  if (controller.GetYButtonReleased()) {
    drive.set_zero_point(pitch);
    drive.reset_pid();
  }

  double p = frc::SmartDashboard::GetNumber("tilt_p", 0.0125);
  double i = frc::SmartDashboard::GetNumber("tilt_i", 0.0);
  double d = frc::SmartDashboard::GetNumber("tilt_d", 0.0);
  drive.set_pid(p, i, d);

  frc::SmartDashboard::PutBoolean("aubal", drive.aubal_enabled);
  frc::SmartDashboard::PutNumber("pitch", pitch - drive.get_zero_point());

  double aubal_x = 0;

  drive.do_auto_balance(pitch, &aubal_x);

  drive.set_power(
    controller.GetRightTriggerAxis() - controller.GetLeftTriggerAxis() - aubal_x,
    std::abs(controller.GetLeftX()) < 0.1 ? 0 : controller.GetLeftX()
  );
}

void Robot::TestPeriodic() {
  // nothing
}

void Robot::SimulationInit() {
  // nothing
}

void Robot::SimulationPeriodic() {
  // nothing
}

#ifndef RUNNING_FRC_TESTS

int main() {
  return frc::StartRobot<Robot>();
}

#endif
