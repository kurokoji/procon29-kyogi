cmake_minimum_required(VERSION 3.0)

find_package(PkgConfig)

set(CMAKE_CXX_STANDARD 17)
project(mikuru CXX)

set(CMAKE_CXX_FLAGS "-Wall -O3 -march=native")

# opencvとzbarは必須
pkg_check_modules(LIBMIKURU opencv zbar REQUIRED)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)

find_package(Boost REQUIRED system)

add_executable(mikuru
  ./mikuru/field.cpp
  ./mikuru/mikuru.cpp
  ./mikuru/color_field.cpp
  ./mikuru/problem_state.cpp
  ./mikuru/qr.cpp)

link_directories(
  ${LIBMIKURU_LIBRARY_DIRS})

target_link_libraries(mikuru
  ${LIBMIKURU_LIBRARIES}
  Boost::system)

include_directories(
  ${LIBMIKURU_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS})
