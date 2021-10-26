cmake_minimum_required(VERSION 3.20)
project(CalculatorApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(UseCCache)
include(UseClangTidy)
include(UseSanitizer)
include(UseCodeCoverage)

set(CMAKE_DEBUG_POSTFIX d)

enable_testing()

add_custom_target(RunAllTests
        COMMAND "${CMAKE_COMMAND}" --build . --target all
        COMMAND "${CMAKE_COMMAND}" --build . --target test
        COMMENT "Running tests"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        VERBATIM)

add_subdirectory(src)
