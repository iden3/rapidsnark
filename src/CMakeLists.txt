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

if(USE_LOGGER)
    set(LIB_SOURCES ${LIB_SOURCES} logger.cpp)
    add_definitions(-DUSE_LOGGER)
endif()

include_directories(
    ../src
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

find_package(OpenMP)

if(OpenMP_CXX_FOUND)
    if(TARGET_PLATFORM MATCHES "android")
        target_link_libraries(prover -static-openmp -fopenmp)
    else()
        target_link_libraries(prover OpenMP::OpenMP_CXX)
    endif()
endif()
