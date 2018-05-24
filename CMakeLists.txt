cmake_minimum_required(VERSION 3.0)

find_package(PkgConfig)

set(CMAKE_CXX_STANDARD 17)
project(mikuru CXX)

set(CMAKE_CXX_FLAGS "-Wall -O3 -march=native")

# opencvとzbarは必須
pkg_check_modules(LIBMIKURU REQUIRED opencv zbar)

include_directories(
  ${LIBMIKURU_INCLUDE_DIRS})

add_executable(mikuru
  ./mikuru/field.cc
  ./mikuru/mikuru.cc)
