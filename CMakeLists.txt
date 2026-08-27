cmake_minimum_required(VERSION 3.18)

if(CMAKE_CXX_COMPILER MATCHES "mingw32" OR CMAKE_C_COMPILER MATCHES "mingw32")
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_PROCESSOR x86_64)
elseif(CMAKE_CXX_COMPILER MATCHES "android" OR CMAKE_C_COMPILER MATCHES "android")
    set(CMAKE_SYSTEM_NAME Android)

    if(NOT CMAKE_ANDROID_NDK)
        message(STATUS "No CMAKE_ANDROID_NDK passed. Trying to find...")

        if(DEFINED ENV{ANDROID_NDK})
            set(CMAKE_ANDROID_NDK ENV{ANDROID_NDK})
        elseif(CMAKE_C_COMPILER MATCHES "(.*)/toolchains/llvm/prebuilt/[^/]+/bin/.*")
            set(CMAKE_ANDROID_NDK "${CMAKE_MATCH_1}")
        elseif(CMAKE_CXX_COMPILER MATCHES "(.*)/toolchains/llvm/prebuilt/[^/]+/bin/.*")
            set(CMAKE_ANDROID_NDK "${CMAKE_MATCH_1}")
        else()
            message(FATAL_ERROR "No CMAKE_ANDROID_NDK found.\nTry setting ANDROID_NDK in environment variables or directly pass it through -DCMAKE_ANDROID_NDK")
        endif()

        message(STATUS "Found ANDROID_NDK at ${CMAKE_ANDROID_NDK}")
    endif()
endif()

project(Bliss VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE BLISS_SRC
    "src/*.cpp"
)

file(GLOB_RECURSE IMGUI_SRC
    "include/imgui/*.cpp"
)

add_library(Bliss SHARED ${BLISS_SRC} ${IMGUI_SRC})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(Bliss PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_subdirectory(external/minhook)

    target_link_libraries(Bliss PRIVATE
        minhook
        d3dcompiler
        d3d11
        dwmapi
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
    # TODO: Hooking lib for android
    # NOT COMPLETE!

    target_link_libraries(Bliss PRIVATE) # TODO: Add libraries (will do)
endif()