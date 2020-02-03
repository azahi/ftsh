FROM debian:bullseye-slim

LABEL maintainer "Azat Bahawi <azahi@teknik.io>"

RUN apt-get update && \
	apt-get install -y \
	build-essential \
	cmake \
	--no-install-recommends && \
	rm -rf /var/lib/apt/lists/*

COPY . /usr/src/minishell
WORKDIR /usr/src/minishell

RUN ( [ -d build ] && rm -rf build ) && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make clean && \
	make all

CMD [ "build/minishell" ]
