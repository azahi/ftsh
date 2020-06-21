cmake_minimum_required(VERSION 3.1...3.18)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
        cmake_policy(VERSION {CMAKE_MAJOR_VERSION.${CMAKE_MINOR_VERSION}})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SH_NAME sh)
set(SH_VERSION 0.0.0)

option(DEBUG_ASAN "AddressSanitizer" OFF)

project(sh
        VERSION 0.0.0
        LANGUAGES C)

add_subdirectory(libft EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
        src/builtin/cd.c
        src/builtin/echo.c
        src/builtin/env.c
        src/builtin/exit.c
        src/builtin/setenv.c
        src/builtin/unsetenv.c
        src/ckmalloc.c
        src/exec.c
        src/exec_util.c
        src/loop.c
        src/main.c
        src/prompt.c
        src/split.c)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
                ft)

target_compile_features(${PROJECT_NAME}
        PRIVATE
                c_std_11
)

set(CMAKE_C_FLAGS_DEBUG
        "-O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls"
)

target_compile_options(${PROJECT_NAME}
        PRIVATE
                -Wall -Wextra -Werror -DSH_NAME="${SH_NAME}" -DSH_VERSION="${SH_VERSION}"
)

if (DEBUG_ASAN)
        set(CMAKE_BUILD_TYPE DEBUG)
        target_compile_options(${PROJECT_NAME}
                PRIVATE
                        -fsanitize=address -fsanitize-address-use-after-scope
        )
        set_target_properties(${PROJECT_NAME}
                PROPERTIES
                        LINK_FLAGS
                                -fsanitize=address)
endif()
