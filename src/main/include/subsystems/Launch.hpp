#pragma once

#include <chrono>

#include <frc/Solenoid.h>
#include <frc/PneumaticsModuleType.h>

#include <frc2/command/SubsystemBase.h>

using namespace std::chrono_literals;

class Launch : public frc2::SubsystemBase {
public:
  Launch();

  void enable_launch();
  void launch();
  void stop();

  bool can_launch = true;

  const std::chrono::milliseconds LAUNCH_LENGTH = 125ms;
  std::chrono::milliseconds launch_start_time;

private:
  frc::Solenoid solenoid {frc::PneumaticsModuleType::CTREPCM, 0};
};
