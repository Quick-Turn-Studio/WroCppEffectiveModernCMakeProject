option(CALCULATOR_PERFORM_CODE_INSPECTION "If ON code inspection is performed during build" OFF)

if (NOT $CACHE{CALCULATOR_PERFORM_CODE_INSPECTION})
    message("Skipping code inspection")
else ()
    message("Configuring files for code inspection")

    find_program(CLANG_TIDY
            NAMES clang-tidy-13
            REQUIRED
            NO_CACHE)

    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY} --use-color)

    add_custom_target(RunCodeInspection
            COMMAND ${CMAKE_COMMAND} --build . --target all
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    file(GENERATE
            OUTPUT "${CMAKE_BINARY_DIR}/.clang-tidy"
            CONTENT "# file to do not inspect generated code in build directory
                    Checks: ''
                    WarningsAsErrors: ''
                    AnalyzeTemporaryDtors: false
                    InheritParentConfig: false
                    FormatStyle: none"
            )
endif ()
