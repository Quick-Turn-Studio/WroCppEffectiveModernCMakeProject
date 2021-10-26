find_package(GTest REQUIRED)
find_package(Catch2 REQUIRED)

set(PARSER_TEST_FILES JsonStringExpressionHistoryParserTests.cpp
        ../src/JsonStringExpressionHistoryParser.cpp)

add_executable(JsonParserTests ${PARSER_TEST_FILES})

include_directories(../src)

target_link_libraries(JsonParserTests PRIVATE GTest::gmock_main)

set(EXPRESSION_PARSER_TEST_FILES testsMain.cpp
        StringExpressionCalculatorTests.cpp
        ../src/StringExpressionCalculator.cpp)

add_executable(ExpressionParserTests ${EXPRESSION_PARSER_TEST_FILES})
target_link_libraries(ExpressionParserTests PRIVATE Catch2::Catch2)

add_test(NAME JsonParserTests
        COMMAND JsonParserTests)

add_test(NAME ExpressionParserTests
        COMMAND ExpressionParserTests)


