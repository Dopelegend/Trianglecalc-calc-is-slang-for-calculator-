cmake_minimum_required(VERSION 4.0)
project(triangleCalculator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(triangleCalculator src/main.cpp
        src/textBox.cpp
        include/textBox.h
        src/TriangleCalculator.cpp
        include/TriangleCalculator.h
        src/Triangle.cpp
        include/Triangle.h)

set_target_properties(triangleCalculator PROPERTIES
        LINK_FLAGS "-static -static-libgcc -static-libstdc++"
        WIN32_EXECUTABLE TRUE

)

target_link_libraries(triangleCalculator
        raylib
        winmm
        gdi32
        opengl32
)