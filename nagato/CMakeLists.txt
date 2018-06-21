cmake_minimum_required(VERSION 3.0)

find_package(PkgConfig)

set(CMAKE_CXX_STANDARD 17)
project(nagato CXX)

set(CMAKE_CXX_FLAGS "-Wall -O3 -march=native")

pkg_check_modules(LIBNAGATO REQUIRED)

add_executable(nagato
  ./nagato/nagato.cpp
  )

link_directories(
  ${LIBNAGATO_LIBRARY_DIRS})

target_link_libraries(nagato
  ${LIBNAGATO_LIBRARIES})

include_directories(
  ${LIBNAGATO_INCLUDE_DIRS})
