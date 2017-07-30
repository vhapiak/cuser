set(UNIT_TESTS unit_tests)
add_executable(
    ${UNIT_TESTS}
    testLastIndexOf.cpp
    testHasStreamOperators.cpp
    testGetArgByType.cpp

    testIOStreamSerializer.cpp
    testFloatSerializer.cpp
    testBoolSerializer.cpp
    testIntegerSerializer.cpp

    testArraySerializer.cpp
    testMapSerializer.cpp
    testVectorSerializer.cpp

    testDefaultSerializer.cpp
    testCustomSerializer.cpp
)
target_link_libraries(
    ${UNIT_TESTS}
    PRIVATE ${CUSER}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main)
target_include_directories(
    ${UNIT_TESTS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_WITH_NLOHMANN_JSON)
    target_sources(
        ${UNIT_TESTS}
        PUBLIC testNlohmannJson.cpp
    )
    target_link_libraries(
        ${UNIT_TESTS}
        PRIVATE nlohmann_json
    )
endif()


add_test(UNIT_TESTS ${UNIT_TESTS})
