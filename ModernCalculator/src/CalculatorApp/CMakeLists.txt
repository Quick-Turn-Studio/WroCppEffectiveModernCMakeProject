set(CALCULATOR_BUILD_VERSION "0" CACHE STRING "Build version")

project(CalculatorApplication LANGUAGES CXX VERSION 1.0.$CACHE{CALCULATOR_BUILD_VERSION})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(APP_NAME Calculator)

aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${APP_NAME} PUBLIC ExpressionCalculatorWidget)
target_link_libraries(${APP_NAME} PUBLIC FileOperations)
target_link_libraries(${APP_NAME} PUBLIC JsonHistoryParser)

set_target_properties(${APP_NAME} PROPERTIES AUTOMOC ON)

target_compile_options(${APP_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -Wno-unused-parameter>
                                   PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -Wno-unused-parameter>
                                   PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
)