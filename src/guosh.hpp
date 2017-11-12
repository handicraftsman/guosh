#pragma once

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

  void write(std::string message, LogLevel level);
  void write(std::string message);

  inline void debug(std::string message) { this->write(message, LogLevel::DEBUG); }
  inline void io(std::string message) { this->write(message, LogLevel::IO); }
  inline void info(std::string message) { this->write(message, LogLevel::INFO); }
  inline void warning(std::string message) { this->write(message, LogLevel::WARNING); }
  inline void error(std::string message) { this->write(message, LogLevel::ERROR); }
  inline void important(std::string message) { this->write(message, LogLevel::IMPORTANT); }
  inline void critical(std::string message) { this->write(message, LogLevel::CRITICAL); }

  std::string name;
  LogLevel level;
  std::string iochars;

  std::string logging_directory;
  std::string fprefix;
  bool should_log_to_files;

  static LogLevel main_level;
  static LogLevel main_file_level;

private:
  std::string format(std::string message, std::string dt, LogLevel level, bool colored = true);
};

}