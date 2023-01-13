// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <cstdarg>

void print(std::string format, ...);
void print(const char *format, ...);
void print_(const char *format, va_list args);
