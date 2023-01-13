// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

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
}

void Robot::TeleopPeriodic() {

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
