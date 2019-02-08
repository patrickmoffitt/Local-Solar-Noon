cmake_minimum_required(VERSION 3.13)
project(local_solar_noon)

set(CMAKE_CXX_STANDARD 11)

add_executable(local_solar_noon main.cpp solar.cpp solar.hpp)
