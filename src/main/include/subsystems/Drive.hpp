#pragma once

#include <cmath>
#include <functional>

#include <frc/motorcontrol/MotorController.h>
#include <frc2/command/SubsystemBase.h>

struct DriveConfig {
  frc::MotorController *ctrl_l, *ctrl_r;
  bool invert_l, invert_r;
  double ramp_x, ramp_r;

  std::function<double ()> power_x, power_r;
};

class Drive : public frc2::SubsystemBase {
public:
  Drive(DriveConfig config);

  void configure_motors();

  void update_power();
  void stop_power();

  void set_power(double x, double r);

private:
  DriveConfig config;
  double cur_x = 0, cur_r = 0;
};
