#pragma once

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

namespace Guosh {

enum class LogLevel : int {
  DEBUG,
  IO,
  INFO,
  WARNING,
  ERROR,
  IMPORTANT,
  CRITICAL,
};

class Logger {
public:
  Logger(Logger&);
  Logger(std::string name = "log", LogLevel level = LogLevel::INFO);

  bool operator==(Logger&);

  void enable_file_logging(std::string directory = "./", std::string prefix = "log");
  void disable_file_logging();

  void write(std::string message, Guosh::LogLevel level, va_list args);
  void write(std::string message, Guosh::LogLevel level, ...);
  void write(std::string message, ...);

  void debug(std::string message, ...);
  void io(std::string message, ...);
  void info(std::string message, ...);
  void warning(std::string message, ...);
  void error(std::string message, ...);
  void important(std::string message, ...);
  void critical(std::string message, ...);

  std::string name;
  LogLevel level;
  std::string iochars;

  std::string logging_directory;
  std::string fprefix;
  bool should_log_to_files;

  static LogLevel main_level;
  static LogLevel main_file_level;

private:
  std::string format(std::string message, std::string dt, LogLevel level, va_list args, bool colored = true);
};

}