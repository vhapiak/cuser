cmake_minimum_required(VERSION 3.1.3)

project(cuser)

set (CMAKE_CXX_STANDARD 11)

find_package(GTest)
if(GTEST_FOUND)
    add_subdirectory(test)
endif(GTEST_FOUND)
