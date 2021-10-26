option(CALCULATOR_USE_COMPILE_CACHE "" ON)

function(UseCcache)
    if (DEFINED CMAKE_CXX_COMPILER_LAUNCHER)
        message("Using compiler launcher provided by user: ${CMAKE_CXX_COMPILER_LAUNCHER}")
        return()
    endif ()
    if (NOT $CACHE{CALCULATOR_USE_COMPILE_CACHE})
        message("Skipping using compilation cache")
        return()
    endif ()
    message("Setting up compilation cache by using CCache")
    find_program(CCACHE_EXECUTABLE ccache)
    if (NOT CCACHE_EXECUTABLE)
        message("CCcache not found. Skipping using ccache")
    endif ()

    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}" CACHE STRING "Compiler launcher path for C++")
    message("CCache found: ${CCACHE_EXECUTABLE}")

endfunction()

UseCcache()