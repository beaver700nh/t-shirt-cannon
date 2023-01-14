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
