cmake_minimum_required(VERSION 3.21)
project(workflow)

set(CMAKE_CXX_STANDARD 14)

add_executable(workflow main.cpp worker.h abstract_factory.h)
