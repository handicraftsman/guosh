#include <particlepm.hpp>

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("guosh");
  p->version(PPM::Version("v0.4.1"));
  p->description("A simple logger for C/++ ");
  p->github(PPM::GitHub("handicraftsman", "guosh"));
  p->license(PPM::License("MIT", "https://github.com/handicraftsman/guosh/blob/master/LICENSE.txt"));

  PPM::TargetPtr lib = p->library("guosh");
  lib->cpp("c++11");
  lib->cpp_files(std::vector<std::string> {
    "src/guosh.cpp",
    "src/guosh-c.cpp"
  });
  lib->cpp_flags(
    flagcat({
      ("-I" + p->pkg_dir() + "/src")
    })
  );
}