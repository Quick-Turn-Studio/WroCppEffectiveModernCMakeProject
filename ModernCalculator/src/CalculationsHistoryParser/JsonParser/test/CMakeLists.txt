find_package(GTest REQUIRED)

set(TEST_NAME JsonParserTests)

aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_NAME} PRIVATE JsonHistoryParser)

add_test(NAME ${TEST_NAME}
        COMMAND ${TEST_NAME})