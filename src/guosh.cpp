#include <guosh.hpp>

Guosh::LogLevel Guosh::Logger::main_level = Guosh::LogLevel::INFO;
Guosh::LogLevel Guosh::Logger::main_file_level = Guosh::LogLevel::WARNING;

Guosh::Logger::Logger(std::string _name, Guosh::LogLevel _level)
: name(_name)
, level(_level)
, iochars(" IO")
, should_log_to_files(false)
, logging_directory("./")
, fprefix("log")
{}

Guosh::Logger::Logger(Logger& other)
: name(other.name)
, level(other.level)
{}

bool Guosh::Logger::operator==(Guosh::Logger& other) {
  return this->name == other.name && this->level == other.level;
}

void Guosh::Logger::write(std::string message, Guosh::LogLevel level, va_list args) {
  static std::mutex mtx;
  static std::ofstream file;
  static std::string filename;

  mtx.lock();

  time_t now = time(0);
  std::string dt = std::string(ctime(&now));
  dt.pop_back();
  if (level >= Guosh::Logger::main_level) {
    std::cerr << this->format(message, dt, level, args, true) << std::endl;
  }
  if (level >= Guosh::Logger::main_file_level) {
    if (should_log_to_files) {
      char* raw_new_f = (char*) malloc(sizeof(16 + fprefix.size()));
      strftime(raw_new_f, 16 + fprefix.size(), (fprefix + "-%d.%m.%Y.log").c_str(), localtime(&now));
      std::string new_filename(raw_new_f);
      if (filename != new_filename) {
        file.close();
        filename = new_filename;
        file.open(logging_directory + "/" + filename, std::ios_base::app);
      }
      std::string dat = this->format(message, dt, level, args, false);
      file << dat << std::endl;
      file.flush();
      free(raw_new_f);
    }
  }

  mtx.unlock();
}

void Guosh::Logger::write(std::string message, Guosh::LogLevel level, ...) {
  va_list args;
  va_start(args, level);
  this->write(message, level, args);
  va_end(args);
}

void Guosh::Logger::write(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, this->level, args);
  va_end(args);
}

void Guosh::Logger::operator()(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, this->level, args);
  va_end(args);
}

void Guosh::Logger::enable_file_logging(std::string directory, std::string prefix) {
  logging_directory = directory;
  fprefix = prefix;
  should_log_to_files = true;
}

void Guosh::Logger::disable_file_logging() {
  should_log_to_files = false;
}

std::string Guosh::Logger::format(std::string _message, std::string dt, Guosh::LogLevel level, va_list args, bool colored) {
  va_list la;
  va_copy(la, args);

  char* cmessage = NULL;
  vasprintf(&cmessage, _message.c_str(), la);
  std::string message = std::string(cmessage);
  free(cmessage);

  // Get level chars
  std::string lvl_chars = "UNK";
  std::string lvl_color = "";
  std::string c_bold = "\x1b[1m";
  std::string c_reset = "\x1b[0m";
  std::string c_creset = "\x1b[39m";

  switch(level) {
  case Guosh::LogLevel::DEBUG:
    lvl_chars = "DBG";
    lvl_color = "\x1b[32m";
    break;
  case Guosh::LogLevel::IO:
    lvl_chars = iochars;
    lvl_color = "\x1b[36m";
    break;
  case Guosh::LogLevel::INFO:
    lvl_chars = "INF";
    lvl_color = "\x1b[34m";
    break;
  case Guosh::LogLevel::WARNING:
    lvl_chars = "WRN";
    lvl_color = "\x1b[33m";
    break;
  case Guosh::LogLevel::ERROR:
    lvl_chars = "ERR";
    lvl_color = "\x1b[31m";
    break;
  case Guosh::LogLevel::IMPORTANT:
    lvl_chars = "IMP";
    lvl_color = "\x1b[37m";
    break;
  case Guosh::LogLevel::CRITICAL:
    lvl_chars = "CRT";
    lvl_color = "\x1b[35m";
    break;
  default:
    break;
  }

  // Return
  if (colored) {
    return
      c_bold
    + lvl_color
    + "["
    + c_creset
    + std::string(dt)
    + lvl_color
    + " | "
    + c_creset
    + lvl_chars
    + lvl_color
    + "] "
    + c_reset
    + name
    + c_bold
    + lvl_color
    + "> "
    + c_reset
    + message
    ;
  } else {
    return
      "["
    + std::string(dt)
    + " | "
    + lvl_chars
    + "] "
    + name
    + "> "
    + message
    ;
  }
}

void Guosh::Logger::debug(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::DEBUG, args); 
  va_end(args);
}

void Guosh::Logger::io(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::IO, args); 
  va_end(args);
}

void Guosh::Logger::info(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::INFO, args); 
  va_end(args);
}

void Guosh::Logger::warning(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::WARNING, args); 
  va_end(args);
}

void Guosh::Logger::error(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::ERROR, args); 
  va_end(args);
}

void Guosh::Logger::important(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::IMPORTANT, args); 
  va_end(args);
}

void Guosh::Logger::critical(std::string message, ...) {
  va_list args;
  va_start(args, message);
  this->write(message, LogLevel::CRITICAL, args); 
  va_end(args);
}
