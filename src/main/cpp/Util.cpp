// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cstring>

#include <frc/smartdashboard/SmartDashboard.h>

#include <wpi/raw_ostream.h>

#include "Constants.h"

#include "Util.hpp"

void print(std::string format, ...) {
  va_list args;
  va_start(args, format);

  print_(format.c_str(), args);

  va_end(args);
}

void print(const char *format, ...) {
  va_list args;
  va_start(args, format);

  print_(format, args);

  va_end(args);
}

void print_(const char *format, va_list args) {
  char buf[UtilConstants::DEBUG_PRINT_STR_MAX_LEN];
  vsnprintf(buf, UtilConstants::DEBUG_PRINT_STR_MAX_LEN, format, args);

  wpi::outs() << buf;
}
