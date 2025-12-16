cmake_minimum_required(VERSION 3.10)
project(dvdBouncingSquare-openGL C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    main.c
    external/glad/src/glad.c
)

target_include_directories(main PRIVATE
    external/glad/include
)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(main PRIVATE glfw)

