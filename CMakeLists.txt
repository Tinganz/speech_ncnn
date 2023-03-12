cmake_minimum_required(VERSION 3.5.1)
project(microbit_voice)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(common)

find_package(PkgConfig)

set(LINK_LIBS)
if (PKG_CONFIG_FOUND)
    pkg_search_module(SDL2 REQUIRED sdl2)
    if(SDL2_FOUND)
        message("sdl2 found")
        set(LINK_LIBS
            ${LINK_LIBS}
            ${SDL2_STATIC_LDFLAGS}
        )
    endif()
endif(PKG_CONFIG_FOUND)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(LINK_LIBS
        ${LINK_LIBS}
        -lpthread
    )
endif()

add_subdirectory(ncnn)
include_directories(
    ${NCNN_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}/ncnn/src
)

set_target_properties(
    ncnn
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

add_subdirectory(imgui)
set_target_properties(
    imgui
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)

add_subdirectory(speech)

include_directories(
    ${IMGUI_INCLUDE_DIRS}
    ${SPEECH_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
)

SET(SDK_MODEL_DIR ${PROJECT_SOURCE_DIR}/models/)
SET(SDK_VOICE_DIR ${PROJECT_SOURCE_DIR}/voices/)
CONFIGURE_FILE(Config.h.in Config.h)

# build example
add_executable(
    capture_wav
    capture_wav.cpp
    SerialPort.cpp
    SerialPort.hpp
    Resample.cpp
    Resample.hpp
    Wave.cpp
    Wave.hpp
)

target_link_libraries(
    capture_wav
    imgui
    ${LINK_LIBS}
)

add_executable(
    ncnn_speech_test
    ncnn_speech.cpp
    entry.cpp
    entry.h
    SerialPort.cpp
    SerialPort.hpp
    Resample.cpp
    Resample.hpp
    Wave.cpp
    Wave.hpp
    ${PROJECT_BINARY_DIR}/Config.h
)

target_link_libraries(
    ncnn_speech_test
    speech
    ncnn
    imgui
    ${LINK_LIBS}
)
