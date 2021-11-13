set(LIB_NAME ExpressionParser)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE .)

target_compile_options(
        ${LIB_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -fPIC>
                    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -fPIC>
                    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
)

add_subdirectory(test)
