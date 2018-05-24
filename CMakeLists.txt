cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
project(mikuru CXX)

set(CMAKE_CXX_FLAGS "-Wall -O3 -march=native")

add_executable(mikuru
  ./mikuru/field.cc
  ./mikuru/mikuru.cc)
