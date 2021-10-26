find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(nlohmann_json REQUIRED)

set(APP_NAME CalculatorWidget)
set(CMAKE_AUTOMOC ON)

aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${APP_NAME} PRIVATE nlohmann_json::nlohmann_json)

if(MSVC)
    target_compile_options(${APP_NAME} PRIVATE /O2)
elseif(APPLE)
    target_compile_options(${APP_NAME} PRIVATE -Wall -O3 -Wno-unused-parameter)
else()
    target_compile_options(${APP_NAME} PRIVATE -Wall -O3 -Wno-unused-parameter)
endif()
