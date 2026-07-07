cmake_minimum_required(VERSION 3.10)

include(cmake/platform.cmake)

set(USE_ASM    ON CACHE BOOL "Use asm implementation for Fr and Fq")
set(USE_OPENMP ON CACHE BOOL "Use OpenMP")
set(USE_MARCH_NATIVE OFF CACHE BOOL "Use -march=native for host builds (host-specific; not portable across CPUs)")
set(USE_LTO    OFF CACHE BOOL "Enable Link Time Optimization (LTO)")

project(rapidsnark LANGUAGES CXX C ASM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Host-only optimization flags
if (USE_MARCH_NATIVE AND NOT CMAKE_CROSSCOMPILING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native")
    message("Using -march=native -mtune=native")
endif()

if (USE_LTO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    message("LTO enabled")
endif()

# Profile-Guided Optimization (host-only, two-phase). PGO=generate builds an
# instrumented binary that writes .gcda profiles to PGO_DIR during a training
# run; PGO=use rebuilds using those profiles. Flags go on both compile and link.
# Only the C++/C glue benefits (the field arithmetic is hand-written NASM).
set(PGO "" CACHE STRING "Profile-guided optimization mode: generate | use | (empty=off)")
set(PGO_DIR "${CMAKE_BINARY_DIR}/pgo-data" CACHE PATH "Directory for PGO .gcda profile data")

if (PGO STREQUAL "generate")
    set(PGO_FLAGS "-fprofile-generate=${PGO_DIR}")
    message("PGO: instrumenting (profiles -> ${PGO_DIR})")
elseif (PGO STREQUAL "use")
    # -fprofile-correction tolerates the multithreaded prover's racy counters;
    # -Wno-missing-profile keeps functions with no profile from erroring.
    set(PGO_FLAGS "-fprofile-use=${PGO_DIR} -fprofile-correction -Wno-missing-profile")
    message("PGO: using profiles from ${PGO_DIR}")
elseif (NOT PGO STREQUAL "")
    message(FATAL_ERROR "PGO must be 'generate', 'use', or empty (got '${PGO}')")
endif()

if (PGO_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PGO_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PGO_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${PGO_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${PGO_FLAGS}")
endif()

message("BITS_PER_CHUNK=" ${BITS_PER_CHUNK})
message("USE_ASM=" ${USE_ASM})
message("USE_OPENMP=" ${USE_OPENMP})
message("CMAKE_CROSSCOMPILING=" ${CMAKE_CROSSCOMPILING})

message("GMP_PREFIX=" ${GMP_PREFIX})
message("GMP_INCLUDE_DIR=" ${GMP_INCLUDE_DIR})
message("GMP_LIB_DIR=" ${GMP_LIB_DIR})

if (NOT EXISTS ${GMP_INCLUDE_FILE_FULLPATH})
    message("WARNING: ${GMP_INCLUDE_FILE_FULLPATH} is not found and so system ${GMP_INCLUDE_FILE} is used.")
endif()

if (NOT EXISTS ${GMP_LIB_FILE_FULLPATH})
    message("WARNING: ${GMP_LIB_FILE_FULLPATH} is not found and so system ${GMP_LIB_FILE} is used.")
    set(GMP_LIB gmp)
endif()


include_directories(BEFORE ${GMP_INCLUDE_DIR})


if(USE_OPENMP)
    find_package(OpenMP)

    if(OpenMP_CXX_FOUND)
        if(TARGET_PLATFORM MATCHES "android")
            message("OpenMP is used")

        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
            message("OpenMP is used")

        else()
            set(OpenMP_CXX_FOUND FALSE)
            message("OpenMP is not used")

        endif()
    endif()
endif()


add_subdirectory(src)


install(TARGETS prover verifier rapidsnark rapidsnarkStatic rapidsnarkStaticFrFq test_prover fr fq
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/app
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES "${GMP_LIB_DIR}/${GMP_LIB_FILE}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES src/prover.h src/verifier.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

enable_testing()
