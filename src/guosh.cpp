#include <guosh.hpp>

Guosh::LogLevel Guosh::Logger::main_level = Guosh::LogLevel::INFO;

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

void Guosh::Logger::write(std::string message, Guosh::LogLevel level) {
  static std::mutex mtx;
  static std::ofstream file;
  static std::string filename;

  if (level >= Guosh::Logger::main_level) {
    mtx.lock();
    time_t now = time(0);
    std::string dt = std::string(ctime(&now));
    dt.pop_back();

    std::cerr << this->format(message, dt, level) << std::endl;

    if (should_log_to_files) {
      char* raw_new_f = (char*) malloc(sizeof(16 + fprefix.size()));
      strftime(raw_new_f, 16 + fprefix.size(), (fprefix + "-%d.%m.%Y.log").c_str(), localtime(&now));
      std::string new_filename(raw_new_f);
      if (filename != new_filename) {
        file.close();
        filename = new_filename;
        file.open(filename);
      }
      std::string dat = this->format(message, dt, level, false);
      file << dat << std::endl;
      free(raw_new_f);
    }
    mtx.unlock();
  }
}

void Guosh::Logger::enable_file_logging(std::string directory, std::string prefix) {
  logging_directory = directory;
  fprefix = prefix;
  should_log_to_files = true;
}

void Guosh::Logger::disable_file_logging() {
  should_log_to_files = false;
}

void Guosh::Logger::write(std::string message) {
  this->write(message, this->level);
}

std::string Guosh::Logger::format(std::string message, std::string dt, Guosh::LogLevel level, bool colored) {
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
