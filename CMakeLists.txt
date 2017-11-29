project(Guosh)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX /usr/ CACHE PATH "Default install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

file(GLOB guosh_SRC src/guosh.cpp src/guosh-c.cpp)
add_library(
  guosh
  SHARED
  ${guosh_SRC}
)
target_include_directories(guosh PUBLIC ./src/)

add_executable(guosh-test src/guosh-test.cpp)
target_include_directories(guosh-test PUBLIC ./src/)
target_link_libraries(guosh-test guosh)

add_executable(guosh-test-c src/guosh-test.c)
target_include_directories(guosh-test-c PUBLIC ./src/)
target_link_libraries(guosh-test-c guosh)

configure_file(
  src/guosh.pc.in
  ${CMAKE_BINARY_DIR}/guosh.pc
)

install(
  TARGETS
    guosh
    guosh-test
    guosh-test-c
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install_files(
  /include
  FILES
    ${CMAKE_SOURCE_DIR}/src/guosh.hpp
    ${CMAKE_SOURCE_DIR}/src/guosh.h
)

install_files(
  /lib/pkgconfig
  FILES
    guosh.pc
)