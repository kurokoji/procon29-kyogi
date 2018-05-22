cmake_minimum_required(VERSION 2.8)

project(mikuru CXX)

set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -O3 -march=native")

add_executable(mikuru
  ./mikuru/field.cc
  ./mikuru/mikuru.cc)
