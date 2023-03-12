#
# Cmake for building imgui
#
cmake_minimum_required(VERSION 3.5.1)
project(IMGUI)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SKIP_RPATH ON)
set(CMAKE_MACOSX_RPATH 0)
if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
if (POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()
if(POLICY CMP0025)
    # reference from https://cmake.org/cmake/help/latest/policy/CMP0025.html
    cmake_policy(SET CMP0025 NEW)
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#if we need run on MacOS before 12.0, then uncomment following code, but not guarantee it's working
#if(APPLE)
#set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0") 
#endif(APPLE)

macro(_OPTION variable description value)
    set(__value ${value})
    set(__condition "")
    set(__varname "__value")
    foreach(arg ${ARGN})
        if(arg STREQUAL "IF" OR arg STREQUAL "if")
            set(__varname "__condition")
        else()
            list(APPEND ${__varname} ${arg})
        endif()
    endforeach()
    unset(__varname)
    if(__condition STREQUAL "")
        set(__condition 2 GREATER 1)
    endif()

    if(${__condition})
        if(__value MATCHES ";")
            if(${__value})
                option(${variable} "${description}" ON)
            else()
                option(${variable} "${description}" OFF)
            endif()
        elseif(DEFINED ${__value})
            if(${__value})
                option(${variable} "${description}" ON)
            else()
                option(${variable} "${description}" OFF)
            endif()
        else()
            option(${variable} "${description}" ${__value})
        endif()
    else()
        unset(${variable} CACHE)
    endif()
    unset(__condition)
    unset(__value)
endmacro()

if(WIN32) 
    add_definitions(-D_CRT_SECURE_NO_WARNINGS) 
    set(CMAKE_COLOR_MAKEFILE OFF CACHE BOOL "Disable Windows color Makefile by Force" FORCE)
endif() 

include_directories( 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}
)

find_package(PkgConfig)

_OPTION(IMGUI_STATIC                "Build ImGui as static library" OFF)
_OPTION(IMGUI_BUILD_EXAMPLE         "Build ImGui example" OFF)
_OPTION(IMGUI_WGPU                  "Build ImGui wgpu backends" OFF)
_OPTION(IMGUI_GL2                   "Build ImGui OpenGL2 backends" ON)
_OPTION(IMGUI_GL3                   "Build ImGui OpenGL3 backends" ON)
_OPTION(IMGUI_SDL2                  "Build ImGui SDL2 backends" ON)
_OPTION(IMGUI_GLFW                  "Build ImGui GLFW backends" ON)
_OPTION(IMGUI_GLUT                  "Build ImGui GLUT backends" OFF)
_OPTION(IMGUI_GLEW                  "Build ImGui GLEW backends" ON)
_OPTION(IMGUI_GLES                  "Build ImGui GLES backends" ON)
_OPTION(IMGUI_MATAL                 "Build ImGui Apple Metal backends(Apple only)" ON IF APPLE)
_OPTION(IMGUI_VULKAN                "Build ImGui Vulkan backends" OFF)
_OPTION(IMGUI_VULKAN_SHADER         "Build ImGui With Vulkan compute support" OFF)
_OPTION(IMGUI_DX9                   "Build ImGui Direct9 backends(Windows only)" ON IF WIN32)
_OPTION(IMGUI_DX10                  "Build ImGui Direct10 backends(Windows only)" ON IF WIN32)
_OPTION(IMGUI_DX11                  "Build ImGui Direct11 backends(Windows only)" ON IF WIN32)
_OPTION(IMGUI_DX12                  "Build ImGui Direct12 backends(Windows only)" ON IF WIN32)
_OPTION(IMGUI_FREETYPE              "Build ImGui with FreeType support" OFF)
_OPTION(IMGUI_ICONS                 "Internal Icons build in library" ON)
_OPTION(IMGUI_APPS                  "build apps base on imgui" ON)
_OPTION(IMGUI_APPLE_APP             "build apple app base on imgui(Apple only)" OFF IF APPLE)

if(IOS AND CMAKE_OSX_ARCHITECTURES MATCHES "arm")
    message(STATUS "Target arch: arm-ios")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon -march=armv7 -ftree-vectorize -fpermissive -fomit-frame-pointer -funroll-loop")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp -mfpu=neon -march=armv7 -ftree-vectorize -fpermissive -fomit-frame-pointer -funroll-loop")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|aarch64)")
    message(STATUS "Target arch: arm64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8 -ftree-vectorize -fpermissive -fomit-frame-pointer -funroll-loops")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8 -ftree-vectorize -fpermissive -fomit-frame-pointer -funroll-loops")
elseif(CMAKE_OSX_ARCHITECTURES MATCHES "x86" OR CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86|x86_64|AMD64)")
    message(STATUS "Target arch: x86")
    if(MSVC OR MSVC_IDE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /arch:AVX /arch:FMA /arch:SSE /arch:SSE2 /arch:SSSE3 /arch:SSE4.1 /arch:SSE4.2")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:AVX2 /arch:AVX /arch:FMA /arch:SSE /arch:SSE2 /arch:SSSE3 /arch:SSE4.1 /arch:SSE4.2")
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -msse4.1 -mssse3 -msse2 -msse -mrelaxed-simd")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.2 -msse4.1 -mssse3 -msse2 -msse -mrelaxed-simd")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mavx")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2 -mavx")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -msse4.1 -mssse3 -msse2 -msse")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.2 -msse4.1 -mssse3 -msse2 -msse")
    endif()
endif()


if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
find_package(OpenGL)

if (IMGUI_VULKAN)
    find_package(Vulkan)
endif(IMGUI_VULKAN)

if (IMGUI_GLUT)
    find_package(GLUT)
endif (IMGUI_GLUT)

if(PKG_CONFIG_FOUND)
    pkg_search_module(ZLIB REQUIRED zlib)
    if(ZLIB_FOUND)
        message("zlib found")
    endif(ZLIB_FOUND)
    if(IMGUI_GLEW)
        pkg_search_module(GLEW REQUIRED glew)
    endif(IMGUI_GLEW)
    if(IMGUI_GLFW)
        pkg_search_module(GLFW REQUIRED glfw3)
    endif(IMGUI_GLFW)
    if(IMGUI_GLUT AND NOT GLUT_FOUND)
        pkg_search_module(GLUT REQUIRED glut)
        if (GLUT_FOUND)
            message("glut found")
        endif (GLUT_FOUND)
    endif(IMGUI_GLUT AND NOT GLUT_FOUND)
    if(IMGUI_VULKAN AND NOT VULKAN_FOUND)
        pkg_search_module(VULKAN REQUIRED vulkan)
        if (VULKAN_FOUND)
            message("vulkan found")
            set (Vulkan_LIBRARY vulkan)
        endif(VULKAN_FOUND)
    endif(IMGUI_VULKAN AND NOT VULKAN_FOUND)
    if(NOT OPENGL_FOUND)
        pkg_search_module(OPENGL REQUIRED gl)
        if (OPENGL_FOUND)
            message("opengl found")
        endif()
    endif()
    if(NOT FREETYPE_FOUND)
        pkg_search_module(FREETYPE REQUIRED freetype2)
        if (FREETYPE_FOUND)
            message("freetype found")
        endif()
    endif()
    pkg_search_module(SDL2 REQUIRED sdl2)
    if(SDL2_FOUND)
        message("sdl2 found")
    endif()
endif(PKG_CONFIG_FOUND)
else()
set(IMGUI_STATIC ON CACHE BOOL "Enable Static ImGui Build by Force" FORCE)
set(IMGUI_OPENGL ON CACHE BOOL "Enable ImGui OpenGL by Force" FORCE)
set(IMGUI_SDL2 ON CACHE BOOL "Enable ImGui SDL2 backends by Force" FORCE)
set(IMGUI_GL2 OFF CACHE BOOL "Build ImGui OpenGL2 backends by Force" FORCE)
set(IMGUI_GL3 ON CACHE BOOL "Build ImGui OpenGL3 backends by Force" FORCE)
set(IMGUI_WGPU ON CACHE BOOL "Build ImGui wgpu backends by Force" FORCE)
set(IMGUI_VULKAN OFF CACHE BOOL "Disable ImGui Vulkan backends" FORCE)
set(IMGUI_VULKAN_SHADER OFF CACHE BOOL "Disable ImGui With Vulkan compute support" FORCE)
set(IMGUI_GLFW ON CACHE BOOL "Enable ImGui GLFW support by Force" FORCE)
set(IMGUI_GLEW OFF CACHE BOOL "Disable ImGui GLEW support" FORCE)
set(IMGUI_GLUT OFF CACHE BOOL "Disable ImGui GLUT support" FORCE)
set(IMGUI_MATAL OFF CACHE BOOL "Disable ImGui Apple Matal support" FORCE)
set(IMGUI_DX9 OFF CACHE BOOL "Disable ImGui Windows DX9 support" FORCE)
set(IMGUI_DX10 OFF CACHE BOOL "Disable ImGui Windows DX10 support" FORCE)
set(IMGUI_DX11 OFF CACHE BOOL "Disable ImGui Windows DX11 support" FORCE)
set(IMGUI_DX12 OFF CACHE BOOL "Disable ImGui Windows DX12 support" FORCE)
set(IMGUI_FREETYPE OFF CACHE BOOL "Disable ImGui with FreeType support" FORCE)
set(IMGUI_APPS OFF CACHE BOOL "Disable apps base on imgui" FORCE)
set(IMGUI_APPLE_APP OFF CACHE BOOL "Disable apple app base on imgui" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2  -s USE_GLFW=3 -s USE_WEBGPU=1 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_MEMORY=128MB -s DISABLE_EXCEPTION_CATCHING=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1 -Wno-unused-command-line-argument")
endif()

# base include
set(IMGUI_INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# base library
set(LINK_LIBS)

if(OPENGL_FOUND)
    set(IMGUI_OPENGL ON)
    message(STATUS "    [ImGui with OpenGL support]")
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${OPENGL_INCLUDE_DIR}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${OPENGL_LIBRARIES}
    )
endif(OPENGL_FOUND)

if(IMGUI_FREETYPE AND FREETYPE_FOUND)
    set(IMGUI_ENABLE_FREETYPE ON)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${FREETYPE_LIBRARIES}
    )
endif(IMGUI_FREETYPE AND FREETYPE_FOUND)

# base sources
set(IMGUI_SRC
    imgui.cpp 
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp
    imgui_helper.cpp
    imgui_user.cpp
    imgui_stdlib.cpp
    dir_iterate.cpp
)

# base headers
set(IMGUI_INCS
    imgui.h
    imgui_internal.h
    imgui_helper.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    immat.h
    imgui_user.h
    imgui_stdlib.h
    dir_iterate.h
    stb_image.h
    stb_image_write.h
    stb_image_resize.h
)

set(IMGUI_FONT_WEIHEI ON)
set(IMGUI_FONT_MONONARROW ON)
set(IMGUI_SRC
    ${IMGUI_SRC}
    fonts/mono_narrow.cpp
    fonts/mono_weihei.cpp
    icons/icons.cpp
    icons/folder.cpp
    icons/fa_solid.cpp
    icons/fa_regular.cpp
)

set(IMGUI_INC_DIRS
    ${IMGUI_INC_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/icons
)
# GLEW Loader support
if (IMGUI_GLEW AND GLEW_FOUND)
    message(STATUS "    [ImGui with GLEW support]")
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${GLEW_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${GLEW_LDFLAGS}
    )
endif(IMGUI_GLEW AND GLEW_FOUND)

# SDL2 support
if(SDL2_FOUND)
    message(STATUS "    [ImGui with SDL2 support]")
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${SDL2_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${SDL2_STATIC_LDFLAGS}
    )
endif(SDL2_FOUND)

# Find Backend Rendering
set(BACKEND_RENDERING NONE)

# Vulkan support
if (VULKAN_FOUND)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${Vulkan_INCLUDE_DIR}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${Vulkan_LIBRARY}
    )
if (IMGUI_VULKAN)
    message(STATUS "    [ImGui backend rendering with Vulkan]")
    set(IMGUI_RENDERING_VULKAN ON)
    set(BACKEND_RENDERING VULKAN)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_vulkan.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_vulkan.h
    )
endif(IMGUI_VULKAN)
endif(VULKAN_FOUND)

# OpenGL
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
if(OPENGL_FOUND AND BACKEND_RENDERING MATCHES NONE)
    if(IMGUI_GL3)
        message(STATUS "    [ImGui backend rendering with OpenGL3]")
        set(IMGUI_RENDERING_GL3 ON)
        set(BACKEND_RENDERING OPENGL3)
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_opengl3.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_opengl3.h
            backends/imgui_impl_opengl3_loader.h
        )
    elseif(IMGUI_GL2)
        message(STATUS "    [ImGui backend rendering with OpenGL2]")
        set(IMGUI_RENDERING_GL2 ON)
        set(BACKEND_RENDERING OPENGL2)
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_opengl2.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_opengl2.h
        )
    endif()
endif()
else()
    set(IMGUI_RENDERING_GL3 ON)
    set(BACKEND_RENDERING OPENGL3)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_opengl3.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_opengl3.h
    )
endif()

# DirectX support
if(WIN32 AND BACKEND_RENDERING MATCHES NONE)
    if(IMGUI_DX12)
        message(STATUS "    [ImGui backend rendering with DX12]")
        set(IMGUI_RENDERING_DX12 ON)
        set(BACKEND_RENDERING DX12)
        set(LINK_LIBS
            ${LINK_LIBS}
            d3d12
        )
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_dx12.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_dx12.h
        )
    elseif(IMGUI_DX11)
        message(STATUS "    [ImGui backend rendering with DX11]")
        set(IMGUI_RENDERING_DX11 ON)
        set(BACKEND_RENDERING DX11)
        set(LINK_LIBS
            ${LINK_LIBS}
            d3d11
        )
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_dx11.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_dx11.h
        )
    elseif(IMGUI_DX10)
        message(STATUS "    [ImGui backend rendering with DX10]")
        set(IMGUI_RENDERING_DX10 ON)
        set(BACKEND_RENDERING DX10)
        set(LINK_LIBS
            ${LINK_LIBS}
            d3d10
        )
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_dx10.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_dx10.h
        )
    elseif(IMGUI_DX9)
        message(STATUS "    [ImGui backend rendering with DX9]")
        set(IMGUI_RENDERING_DX9 ON)
        set(BACKEND_RENDERING DX9)
        set(LINK_LIBS
            ${LINK_LIBS}
            d3d9
        )
        set(IMGUI_SRC
            ${IMGUI_SRC}
            backends/imgui_impl_dx9.cpp
        )
        set(IMGUI_INCS
            ${IMGUI_INCS}
            backends/imgui_impl_dx9.h
        )
    endif(IMGUI_DX12)
    if(NOT BACKEND_RENDERING MATCHES NONE)
        set(LINK_LIBS
            ${LINK_LIBS}
            d3dcompiler
            dxgi
        )
    endif()
endif()

# Apple metal support
if (APPLE AND IMGUI_MATAL AND BACKEND_RENDERING MATCHES NONE)
    message(STATUS "    [ImGui backend rendering with Matal]")
    set(IMGUI_RENDERING_MATAL ON)
    set(BACKEND_RENDERING MATAL)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_metal.mm
        backends/imgui_impl_osx.mm
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_metal.h
        backends/imgui_impl_osx.h
    )
endif()

# Find Backend platform
# SDL2 Support
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
if (IMGUI_SDL2 AND SDL2_FOUND)
    message(STATUS "    [ImGui backend platform with SDL2]")
    set(IMGUI_PLATFORM_SDL2 ON)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        #backends/imgui_impl_sdlrenderer.cpp
        backends/imgui_impl_sdl.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        #backends/imgui_impl_sdlrenderer.h
        backends/imgui_impl_sdl.h
    )
endif(IMGUI_SDL2 AND SDL2_FOUND)
else()
    set(IMGUI_PLATFORM_SDL2 ON)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        #backends/imgui_impl_sdlrenderer.cpp
        backends/imgui_impl_sdl.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        #backends/imgui_impl_sdlrenderer.h
        backends/imgui_impl_sdl.h
    )

    set(IMGUI_PLATFORM_WGPU ON)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_wgpu.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_wgpu.h
    )

    set(IMGUI_PLATFORM_GLFW ON)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_glfw.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_glfw.h
    )
endif()

# GLFW support
if (IMGUI_GLFW AND GLFW_FOUND)
    message(STATUS "    [ImGui backend platform with GLFW]")
    set(IMGUI_PLATFORM_GLFW ON)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${GLFW_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${GLFW_LDFLAGS}
    )
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_glfw.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_glfw.h
    )
endif(IMGUI_GLFW AND GLFW_FOUND)

# GLUT support
if (IMGUI_GLUT AND GLUT_FOUND)
    message(STATUS "    [ImGui backend platform with GLUT]")
    set(IMGUI_PLATFORM_GLUT ON)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${GLUT_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${GLUT_LDFLAGS}
        ${GLUT_LIBRARY}
    )
    if (NOT APPLE AND NOT LINUX)
        set(LINK_LIBS
            ${LINK_LIBS}
            -lGL
        )
    endif(NOT APPLE AND NOT LINUX)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_glut.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_glut.h
    )
endif(IMGUI_GLUT AND GLUT_FOUND)

# Win32 Support
if(WIN32)
    message(STATUS "    [ImGui backend platform with Win32]")
    set(IMGUI_PLATFORM_WIN32 ON)
    set(IMGUI_SRC
        ${IMGUI_SRC}
        backends/imgui_impl_win32.cpp
    )
    set(IMGUI_INCS
        ${IMGUI_INCS}
        backends/imgui_impl_win32.h
    )
endif(WIN32)

set(IMGUI_INC_DIRS
    ${IMGUI_INC_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

# ImVulkanShader
if(IMGUI_VULKAN_SHADER)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(addon/ImVulkanShader)
    set(IMGUI_INC_DIRS
        ${IMGUI_INC_DIRS}
        ${VKSHADER_INCLUDE_DIRS}
    )
    set(LINK_LIBS
        ${LINK_LIBS}
        ${VKSHADER_LIBRARYS}
    )
endif(IMGUI_VULKAN_SHADER)

# ImGuiFileDialog
set(IMGUI_SRC
    ${IMGUI_SRC}
    ImGuiFileDialog.cpp
)
set(IMGUI_INCS
    ${IMGUI_INCS}
    ImGuiFileDialog.h
)

if(ZLIB_FOUND)
    add_definitions(-DIMGUI_USE_ZLIB)
    set(LINK_LIBS
        ${LINK_LIBS}
        ${ZLIB_LDFLAGS}
    )
endif(ZLIB_FOUND)

if(NOT IMGUI_STATIC)
set(IMGUI_SHARED_LIBRARY ON)
endif(NOT IMGUI_STATIC)
# Build library
configure_file(imconfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/imconfig.h)

set(IMGUI_INC_DIRS
    ${IMGUI_INC_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(${IMGUI_INC_DIRS})

if(IMGUI_STATIC)
set(LIBRARY STATIC)
else(IMGUI_STATIC)
set(LIBRARY SHARED)
endif(IMGUI_STATIC)

set(IMGUI_VERSION_MAJOR 1)
set(IMGUI_VERSION_MINOR 89)
set(IMGUI_VERSION_PATCH 20)
set(IMGUI_VERSION_BUILD 06)
set(IMGUI_VERSION_STRING ${IMGUI_VERSION_MAJOR}.${IMGUI_VERSION_MINOR}.${IMGUI_VERSION_PATCH}.${IMGUI_VERSION_BUILD})

add_library(imgui ${LIBRARY} ${IMGUI_SRC} ${IMGUI_INCS})
set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
if(NOT IMGUI_STATIC)
target_link_libraries(imgui ${LINK_LIBS})
set_target_properties(imgui PROPERTIES VERSION ${IMGUI_VERSION_STRING} SOVERSION ${IMGUI_VERSION_MAJOR})
endif(NOT IMGUI_STATIC)
# Build Tools
if (APPLE AND IMGUI_MATAL AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(
        imgui 
        PUBLIC "-fobjc-arc"
    )
endif()

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    set(IMGUI_LIBRARYS imgui ${LINK_LIBS} PARENT_SCOPE )
    set(IMGUI_INCLUDES ${IMGUI_INCS} PARENT_SCOPE )
    set(IMGUI_INCLUDE_DIRS ${IMGUI_INC_DIRS} PARENT_SCOPE )
endif()