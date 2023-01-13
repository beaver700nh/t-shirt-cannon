#pragma once

#include <string>
#include <cstdarg>

void print(std::string format, ...);
void print(const char *format, ...);
void print_(const char *format, va_list args);
