cmake_minimum_required(VERSION 3.18)
project(Bliss VERSION 0.1 LANGUAGES CXX)

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

add_subdirectory(external/minhook)

target_link_libraries(Bliss PRIVATE
    minhook
    d3dcompiler
    d3d11
    dwmapi
)