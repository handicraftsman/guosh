#include <guosh.hpp>

int main() {
  Guosh::Logger::main_level = Guosh::LogLevel::DEBUG;
  Guosh::Logger log;
  log.enable_file_logging("./", "test-c++");

  log.write("write()");
  log("operator()");
  log.debug("debug");
  log.io("io");
  log.info("info");
  log.warning("warning");
  log.error("error");
  log.important("important");
  log.critical("critical %s bar", "foo");
}