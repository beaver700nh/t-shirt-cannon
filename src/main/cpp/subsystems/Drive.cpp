#include <algorithm>
#include <cmath>

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsystems/Drive.hpp"

Drive::Drive(DriveConfig config) {
  this->config = config;
}

void Drive::configure_motors() {
  config.ctrl_l->SetInverted(config.invert_l);
  config.ctrl_r->SetInverted(config.invert_r);
}

void Drive::stop_power() {
  set_power(0.0, 0.0);
}

void Drive::set_power(double x, double r) {
  if (x > cur_x) {
    cur_x = fmin(x, cur_x + config.ramp_x);
  }
  if (x < cur_x) {
    cur_x = fmax(x, cur_x - config.ramp_x);
  }

  if (r > cur_r) {
    cur_r = fmin(r, cur_r + config.ramp_r);
  }
  if (r < cur_r) {
    cur_r = fmax(r, cur_r - config.ramp_r);
  }

  config.ctrl_l->Set(cur_x - cur_r);
  config.ctrl_r->Set(cur_x + cur_r);
}

void Drive::do_auto_balance(double pitch, double *x_out) {
  if (!aubal_enabled) {
    return;
  }

  if ((!aubal_in_use && std::abs(pitch) > aubal_thres_on) || (aubal_in_use && std::abs(pitch) > aubal_thres_off)) {
    aubal_in_use = true;

    *x_out = std::clamp(pid.Calculate(pitch), -0.3, 0.3);

    frc::SmartDashboard::PutNumber("aubal_adjust_x", *x_out);
  }
  else {
    aubal_in_use = false;
  }
}

void Drive::toggle_auto_balance() {
  aubal_enabled = !aubal_enabled;
}

double Drive::get_zero_point() {
  return pid.GetSetpoint();
}

void Drive::set_zero_point(double pitch) {
  pid.SetSetpoint(pitch);
}

void Drive::reset_pid() {
  pid.Reset();
}

void Drive::set_pid(double p, double i, double d) {
  pid.SetPID(p, i, d);
}
