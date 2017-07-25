set(UNIT_TESTS unit_tests)
add_executable(
    ${UNIT_TESTS}
    testLastIndexOf.cpp
    testHasStreamOperators.cpp

    testIOStreamSerializer.cpp
    testFloatSerializer.cpp
)
target_link_libraries(
    ${UNIT_TESTS}
    PRIVATE ${CUSER}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main)
target_include_directories(
    ${UNIT_TESTS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(UNIT_TESTS ${UNIT_TESTS})
