cmake_minimum_required(VERSION 3.14)

project(ftsh C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/libft)

include_directories(include
        lib/libft/include)

add_executable(ftsh
        src/env.c
        src/main.c)

target_link_libraries(ftsh ft)
