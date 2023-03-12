# Install script for directory: /Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/libncnn.1.0.23.03.11.dylib"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/libncnn.1.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.1.0.23.03.11.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.1.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "libncnn.1.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/libncnn.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libncnn.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libncnn.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ncnn" TYPE FILE FILES
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/allocator.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/benchmark.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/blob.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/c_api.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/command.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/cpu.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/datareader.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/gpu.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/layer.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/layer_shader_type.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/layer_type.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/mat.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/modelbin.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/net.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/option.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/paramdict.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/pipeline.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/pipelinecache.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/simpleocv.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/simpleomp.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/simplestl.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/ncnn/src/vulkan_header_fix.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/ncnn_export.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/layer_shader_type_enum.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/layer_type_enum.h"
    "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/platform.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ncnn" TYPE FILE FILES "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/ncnnConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/tingan/Desktop/未命名文件夹/speech_ncnn/build/ncnn/src/ncnn.pc")
endif()

