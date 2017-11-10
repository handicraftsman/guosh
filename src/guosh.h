#pragma once

typedef struct GuoshLogger GuoshLogger;

typedef enum GuoshLogLevel {
  GuoshLogLevel_DEBUG,
  GuoshLogLevel_IO,
  GuoshLogLevel_INFO,
  GuoshLogLevel_WARNING,
  GuoshLogLevel_ERROR,
  GuoshLogLevel_IMPORTANT,
  GuoshLogLevel_CRITICAL,
} GuoshLogLevel;

void guosh_set_main_level(GuoshLogLevel level);
GuoshLogLevel guosh_get_main_level();

GuoshLogger* guosh_logger_new(char* name, GuoshLogLevel level);
void guosh_logger_destroy(GuoshLogger* logger);
void guosh_logger_set_iochars(GuoshLogger* log, const char* chars);
const char* guosh_logger_get_iochars(GuoshLogger* log);
void guosh_logger_write(GuoshLogger* logger, char* message);
void guosh_logger_writel(GuoshLogger* logger, char* message, GuoshLogLevel level);
void guosh_logger_debug(GuoshLogger* logger, char* message);
void guosh_logger_io(GuoshLogger* logger, char* message);
void guosh_logger_info(GuoshLogger* logger, char* message);
void guosh_logger_warning(GuoshLogger* logger, char* message);
void guosh_logger_error(GuoshLogger* logger, char* message);
void guosh_logger_important(GuoshLogger* logger, char* message);
void guosh_logger_critical(GuoshLogger* logger, char* message);