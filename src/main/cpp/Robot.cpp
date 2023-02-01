#include <chrono>
#include <cmath>

#include <frc2/command/CommandScheduler.h>

#include "Robot.hpp"

ADIS16470_IMU imu = new ADIS16470_IMU()

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
  container
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
  drive.set_power(
    controller.GetRightTriggerAxis() - controller.GetLeftTriggerAxis(),
    std::abs(controller.GetLeftX()) < 0.1 ? 0 : controller.GetLeftX()
  );

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
