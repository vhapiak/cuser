set(UNIT_TESTS unit_tests)
add_executable(
    ${UNIT_TESTS}
    testLastIndexOf.cpp
    testHasStreamOperators.cpp
)
target_link_libraries(
    ${UNIT_TESTS}
    PRIVATE ${CUSER}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main)

add_test(UNIT_TESTS ${UNIT_TESTS})
