#include <chrono>

#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/Commands.h>
#include <units/time.h>

#include "subsystems/Launch.hpp"

Launch::Launch() {
  stop();
}

void Launch::enable_launch() {
  can_launch = true;
}

void Launch::launch() {
  if (!can_launch) {
    return;
  }

  can_launch = false;
  solenoid.Set(true);

  launch_start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  );
}

void Launch::stop() {
  solenoid.Set(false);
}
