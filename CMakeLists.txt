cmake_minimum_required(VERSION 4.0)
project(triangleCalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(triangleCalculator src/main.cpp
        src/textBox.cpp
        include/textBox.h
        src/TriangleCalculator.cpp
        include/TriangleCalculator.h
        src/Triangle.cpp
        include/Triangle.h)

set(RAYLIB_PATH "C:/C++/Libs/RayLib/raylib-5.5_win64_mingw-w64")

target_include_directories(triangleCalculator PRIVATE
        ${RAYLIB_PATH}/include
)

target_link_directories(triangleCalculator PRIVATE
        ${RAYLIB_PATH}/lib
)

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