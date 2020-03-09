cmake_minimum_required(VERSION 3.1...3.16)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
        cmake_policy(VERSION {CMAKE_MAJOR_VERSION.${CMAKE_MINOR_VERSION}})
endif()

project(minishell
        VERSION 0.1
        LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG OFF)
if (DEBUG)
        add_definitions(-DDEBUG)
        set(CMAKE_BUILD_TYPE Debug)
endif(DEBUG)

add_subdirectory(lib/libft)

add_executable(minishell
        src/builtin/cd.c
        src/builtin/echo.c
        src/builtin/env.c
        src/builtin/exit.c
        src/builtin/setenv.c
        src/builtin/unsetenv.c
        src/env.c
        src/error.c
        src/exec.c
        src/main.c
        src/parser.c
        src/prompt.c
        src/putenv.c)
target_link_libraries(minishell
        PUBLIC ft)
