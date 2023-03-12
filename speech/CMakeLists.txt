cmake_minimum_required(VERSION 3.5.1)
project(speech)

find_package(OpenMP)
# For CMake < 3.9, we need to make the target ourselves
if (APPLE AND OPENMP_FOUND)
    message(STATUS "Speech Use OpenMP")
    add_definitions(-DENABLE_OMP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(LINK_LIBS ${LINK_LIBS} ${OpenMP_libomp_LIBRARY})
    include_directories(${OpenMP_CXX_INCLUDE_DIR})
else()
    if(NOT TARGET OpenMP::OpenMP_CXX AND (OpenMP_CXX_FOUND OR OPENMP_FOUND))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    endif()
endif()

SET(SPEECH_SOURCE_FILES
    Speech.cpp
    FeatureExtractor.cpp
    SymbolTable.cpp
)

SET(SPEECH_HEADER_FILES
    Speech.hpp
    FeatureExtractor.h
    SymbolTable.h
    table.h
)

SET(FBANK_SOURCE_FILES
    fbank/feature-fbank.cc
    fbank/feature-functions.cc
    fbank/feature-window.cc
    fbank/fftsg.c
    fbank/log.cc
    fbank/mel-computations.cc
    fbank/online-feature.cc
    fbank/rfft.cc
)

SET(FBANK_HEADER_FILES
    fbank/feature-fbank.h
    fbank/feature-functions.h
    fbank/feature-window.h
    fbank/mel-computations.h
    fbank/online-feature.h
    fbank/rfft.h
    fbank/log.h
)

ADD_LIBRARY(speech
            STATIC 
            ${SPEECH_SOURCE_FILES} 
            ${SPEECH_HEADER_FILES} 
            ${FBANK_SOURCE_FILES}
            ${FBANK_HEADER_FILES}
)

set_property(TARGET speech PROPERTY POSITION_INDEPENDENT_CODE ON)

TARGET_LINK_LIBRARIES(
    speech
    ${LINK_LIBS}
)

add_executable(
    make_language_table
    make_table.cpp
    SymbolTable.cpp
    SymbolTable.h
)

set(SPEECH_LIBRARYS speech ${LINK_LIBS} PARENT_SCOPE )
set(SPEECH_INCLUDES ${SPEECH_HEADER_FILES} PARENT_SCOPE )
set(SPEECH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE )
