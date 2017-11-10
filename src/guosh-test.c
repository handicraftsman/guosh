#include <guosh.h>

int main() {
  guosh_set_main_level(GuoshLogLevel_DEBUG);
  GuoshLogger* log = guosh_logger_new("log", GuoshLogLevel_INFO);
  guosh_logger_enable_file_logging(log, "./", "test-c");

  guosh_logger_debug(log, "debug");
  guosh_logger_io(log, "io");
  guosh_logger_info(log, "info");
  guosh_logger_warning(log, "warning");
  guosh_logger_error(log, "error");
  guosh_logger_important(log, "important");
  guosh_logger_critical(log, "critical");
  
  guosh_logger_destroy(log);
  return 0;
}