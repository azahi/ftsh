cmake_minimum_required(VERSION 3.14)

project(ftsh C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/libft)

include_directories(
        lib/libft/include)

add_executable(ftsh
        src/builtin/cd.c
        src/builtin/echo.c
        src/builtin/env.c
        src/builtin/exit.c
        src/builtin/setenv.c
        src/builtin/unsetenv.c
        src/main.c)

target_link_libraries(ftsh ft)
