find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(LIB_NAME ExpressionCalculatorWidget)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} SHARED ${SRC_FILES})

if (MSVC)
    target_compile_definitions(${LIB_NAME} INTERFACE "CALCULATOR_WIDGET_API=__declspec(dllimport)")
    target_compile_definitions(${LIB_NAME} PRIVATE "CALCULATOR_WIDGET_API=__declspec(dllexport)")
else ()
    target_compile_definitions(${LIB_NAME} PUBLIC "CALCULATOR_WIDGET_API=")
endif ()

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${LIB_NAME} PUBLIC ExpressionParser)

set_target_properties(${LIB_NAME} PROPERTIES AUTOMOC ON)

target_compile_options(
        ${LIB_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -Wno-unused-parameter>
                    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -Wno-unused-parameter>
                    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
)