#pragma once

#include <frc/Joystick.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/ADIS16470_IMU.h>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include "subsystems/Drive.hpp"
#include "subsystems/Launch.hpp"

#include "RobotContainer.h"

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;

  /**
   * This function is called every 20 ms, no matter the mode. Use
   * this for items like diagnostics that you want to run during disabled,
   * autonomous, teleoperated and test.
   *
   * This runs after the mode specific periodic functions, but before
   * LiveWindow and SmartDashboard integrated updating.
   */
  void RobotPeriodic() override;

  /**
   * This function is called once each time the robot enters Disabled mode. You
   * can use it to reset any subsystem information you want to clear when the
   * robot is disabled.
   */
  void DisabledInit() override;

  void DisabledPeriodic() override;

  /**
   * This autonomous runs the autonomous command selected by your
   * RobotContainer class.
   */
  void AutonomousInit() override;

  void AutonomousPeriodic() override;

  void TeleopInit() override;

  /**
   * This function is called periodically during operator control.
   */
  void TeleopPeriodic() override;

  /**
   * This function is called periodically during test mode.
   */
  void TestPeriodic() override;

  /**
   * This function is called once when the robot is first started up.
   */
  void SimulationInit() override;

  /**
   * This function is called periodically whilst in simulation.
   */
  void SimulationPeriodic() override;

private:
  RobotContainer container;

  frc::ADIS16470_IMU imu;

  frc::XboxController controller {0};

  frc::MotorControllerGroup motor_controller_l {
    std::vector<std::reference_wrapper<frc::MotorController>> {
      *(frc::MotorController *) new ctre::phoenix::motorcontrol::can::WPI_VictorSPX {1},
      *(frc::MotorController *) new ctre::phoenix::motorcontrol::can::WPI_VictorSPX {2}
    }
  };
  frc::MotorControllerGroup motor_controller_r {
    std::vector<std::reference_wrapper<frc::MotorController>> {
      *(frc::MotorController *) new ctre::phoenix::motorcontrol::can::WPI_VictorSPX {3},
      *(frc::MotorController *) new ctre::phoenix::motorcontrol::can::WPI_VictorSPX {4}
    }
  };

  Drive drive {
    DriveConfig {
      &motor_controller_l, &motor_controller_r,
      false, true,
      0.04, 0.04
    }
  };

  Launch launch;
};
