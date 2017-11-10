#pragma once

#include <iostream>
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

  static LogLevel main_level;

private:
  std::string format(std::string message, LogLevel level);
};

}