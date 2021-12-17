cmake_minimum_required(VERSION 3.21)
project(workflow)

set(CMAKE_CXX_STANDARD 14)

find_package(Catch2 3 REQUIRED)

add_executable(sort-test blocks.h blocks.cpp tests/blocks_test.cpp)
target_link_libraries(sort-test PRIVATE Catch2::Catch2WithMain)

add_executable(workflow-test workflow.cpp workflow.h factory.h block_creators.cpp block_creators.h blocks.h blocks.cpp tests/workflow_test.cpp)
target_link_libraries(workflow-test PRIVATE Catch2::Catch2WithMain)

add_executable(workflow main.cpp worker.h factory.h exceptions.h workflow.cpp workflow.h blocks.cpp blocks.h block_creators.cpp block_creators.h creator.h factory.cpp)
