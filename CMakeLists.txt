cmake_minimum_required(VERSION 3.5.2)

set(CUSER cuser)
project(${CUSER})

set (CMAKE_CXX_STANDARD 11)

add_library(${CUSER} INTERFACE)
target_include_directories(
    ${CUSER}
    INTERFACE ${PROJECT_SOURCE_DIR}/include)

find_package(GTest)
if(GTEST_FOUND)
    enable_testing()
    add_subdirectory(test)
endif(GTEST_FOUND)
