#include <frc2/command/CommandScheduler.h>

#include "Util.hpp"

#include "Robot.hpp"

void Robot::RobotInit() {
  print("Robot initialized.\n");
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void Robot::DisabledInit() {
  print("Robot disabled.\n");
  drive.stop_power();
}

void Robot::DisabledPeriodic() {
  // nothing
}

void Robot::AutonomousInit() {
  print("Autonomous running.\n");
}

void Robot::AutonomousPeriodic() {
  // nothing
}

void Robot::TeleopInit() {
  print("Teleop started.\n");
  drive.configure_motors();
}

void Robot::TeleopPeriodic() {
  drive.set_power(
    controller.GetRightTriggerAxis() - controller.GetLeftTriggerAxis(),
    controller.GetLeftX()
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
