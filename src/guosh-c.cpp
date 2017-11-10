#include <guosh.hpp>

extern "C" {

void guosh_set_main_level(Guosh::LogLevel level) {
  Guosh::Logger::main_level = level;
}

Guosh::LogLevel guosh_get_main_level(Guosh::LogLevel level) {
  return Guosh::Logger::main_level;
}

Guosh::Logger* guosh_logger_new(char* name, Guosh::LogLevel level) {
  return new Guosh::Logger(std::string(name), level);
}

void guosh_logger_destroy(Guosh::Logger* logger) {
  delete logger;
}

void guosh_logger_set_iochars(Guosh::Logger* logger, const char* chars) {
  logger->iochars = std::string(chars);
}

const char* guosh_logger_get_iochars(Guosh::Logger* logger) {
  return logger->iochars.c_str();
}

void guosh_logger_write(Guosh::Logger* logger, char* message) {
  logger->write(std::string(message));
}

void guosh_logger_writel(Guosh::Logger* logger, char* message, Guosh::LogLevel level) {
  logger->write(std::string(message), level);
}

void guosh_logger_debug(Guosh::Logger* logger, char* message) {
  logger->debug(std::string(message));
}

void guosh_logger_io(Guosh::Logger* logger, char* message) {
  logger->io(std::string(message));
}

void guosh_logger_info(Guosh::Logger* logger, char* message) {
  logger->info(std::string(message));
}

void guosh_logger_warning(Guosh::Logger* logger, char* message) {
  logger->warning(std::string(message));
}

void guosh_logger_error(Guosh::Logger* logger, char* message) {
  logger->error(std::string(message));
}

void guosh_logger_important(Guosh::Logger* logger, char* message) {
  logger->important(std::string(message));
}

void guosh_logger_critical(Guosh::Logger* logger, char* message) {
  logger->critical(std::string(message));
}

}