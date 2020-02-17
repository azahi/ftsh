#!/usr/bin/env zsh

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DDEBUG=ON || exit 1

cmake --build build --target all || exit 1

./build/minishell 2> >(while read line; do echo -e "\e[01;31m$line\e[0m" >&2; done)
