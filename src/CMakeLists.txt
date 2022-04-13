if(USE_ASM)
    add_definitions(-DUSE_ASM)
endif()

if(OpenMP_CXX_FOUND)
    add_definitions(-DUSE_OPENMP)
    add_compile_options(${OpenMP_CXX_FLAGS})
endif()

set(LIB_SOURCES
    binfile_utils.hpp
    binfile_utils.cpp
    zkey_utils.hpp
    zkey_utils.cpp
    wtns_utils.hpp
    wtns_utils.cpp
    logger.hpp
    logger.cpp
    fileloader.cpp
    fileloader.hpp
    prover.cpp
    prover.h
    ../depends/ffiasm/c/misc.cpp
    ../depends/ffiasm/c/naf.cpp
    ../depends/ffiasm/c/splitparstr.cpp
    ../depends/ffiasm/c/alt_bn128.cpp
    ../build/fq.hpp
    ../build/fq.cpp
    ../build/fr.hpp
    ../build/fr.cpp
    )

if(USE_ASM)
    set(LIB_SOURCES ${LIB_SOURCES} ../build/fq.o ../build/fr.o)
endif()

if(USE_LOGGER)
    set(LIB_SOURCES ${LIB_SOURCES} logger.cpp)
    add_definitions(-DUSE_LOGGER)
endif()

include_directories(
    ../src
    ../build
    ../depends/ffiasm/c
    ../depends/json/single_include)


add_library(rapidsnark STATIC ${LIB_SOURCES})

add_executable(prover main_prover.cpp)

target_link_libraries(prover rapidsnark ${GMP_LIB})

if(USE_LOGGER)
    target_link_libraries(prover pthread)
endif()

if(USE_SODIUM)
    target_link_libraries(prover sodium)
endif()


if(OpenMP_CXX_FOUND)

    if(TARGET_PLATFORM MATCHES "android")
        target_link_libraries(prover -static-openmp -fopenmp)

    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        target_link_libraries(prover OpenMP::OpenMP_CXX)
    endif()

endif()


set(UNIT_TEST_SOURCES
    ../build/fq.hpp
    ../build/fq.cpp
    ../build/fr.hpp
    ../build/fr.cpp
    )

if(USE_ASM)
    set(UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES} ../build/fq.o ../build/fr.o)
endif()

add_executable(test_prover test_prover.cpp ${UNIT_TEST_SOURCES})

target_link_libraries(test_prover ${GMP_LIB})
