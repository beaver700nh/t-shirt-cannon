#pragma once

#include <cmath>
#include <functional>

#include <frc/motorcontrol/MotorController.h>
#include <frc/controller/PIDController.h>

#include <frc2/command/SubsystemBase.h>

struct DriveConfig {
  frc::MotorController *ctrl_l, *ctrl_r;
  bool invert_l, invert_r;
  double ramp_x, ramp_r;
};

class Drive : public frc2::SubsystemBase {
public:
  Drive(DriveConfig config);

  void configure_motors();

  void update_power();
  void stop_power();

  void set_power(double x, double r);

  void do_auto_balance(double pitch, double *x_out);
  void toggle_auto_balance();

  double get_zero_point();
  void set_zero_point(double pitch);

  void reset_pid();
  void set_pid(double p, double i, double d);

  bool aubal_enabled = false;

private:
  DriveConfig config;

  double cur_x = 0, cur_r = 0;

  double aubal_thres_on = 8;
  double aubal_thres_off = 4;
  bool aubal_in_use = false;

  frc::PIDController pid {0, 0, 0};
};
