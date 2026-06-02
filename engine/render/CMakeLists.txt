cmake_minimum_required(VERSION 3.10.2)

project(render)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-deprecated")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG ")

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(EXTRA_DIR "${ROOT_DIR}/../../extra")
set(COMMON_DIR "${ROOT_DIR}/../common")
set(EXTRA_COMMON_DIR "${COMMON_DIR}")
set(EXTRA_FFMPEG_ROOT "${EXTRA_DIR}/ffmpeg")

set(SRC_LIST
        opengl/OpenglVideoRender.cpp
        opengl/common/OpenglContext.cpp
        opengl/common/OpenGlUtil.cpp
        opengl/filter/ShaderFactory.cpp
        opengl/filter/BaseFilter.cpp
        opengl/filter/OpenglFilter.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    add_definitions(-DPLATFORM_ANDROID)
    set(TARGET_PLATFORM android)
    set(CMAKE_ANDROID_NDK $ENV{ANDROID_NDK})
    set(SRC_LIST
            ${SRC_LIST}
            opengl/android/EglContext.cpp
            android/AudioTrackRender.cpp
            android/MediacodecRender.cpp
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "OHOS")
    add_definitions(-D__HARMONY__)
    set(TARGET_PLATFORM harmony)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
    set(SRC_LIST
            ${SRC_LIST}
            opengl/harmony/egl_context.cc
            harmony/HarmonyVideoRender.cpp
            harmony/HarmonyAudioRender.cpp
    )
else ()
    message(FATAL_ERROR "Don't support ${CMAKE_SYSTEM_NAME}!")
endif ()

include_directories("${EXTRA_FFMPEG_ROOT}/include"
        "${EXTRA_COMMON_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(render SHARED ${SRC_LIST})

target_link_options(render PRIVATE "-Wl,-z,max-page-size=16384")

if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(CMAKE_SYSTEM_VERSION 21)
    target_link_libraries(
            render
            common
            EGL
            GLESv2
            android
            jnigraphics
            log
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "OHOS")
    target_link_libraries(
            render
            common
            native_media_core
            native_window
            ohaudio
            EGL
            GLESv3
    )
else ()
    message(FATAL_ERROR "Don't support ${CMAKE_SYSTEM_NAME}!")
endif ()
