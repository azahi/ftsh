FROM debian:bullseye-slim

LABEL maintainer "Azat Bahawi <azahi@teknik.io>"

RUN apt-get update && \
	apt-get install -y \
	build-essential \
	cmake \
	gcc \
	--no-install-recommends && \
	rm -rf /var/lib/apt/lists/*

COPY . /usr/src/ftsh
WORKDIR /usr/src/ftsh

RUN mkdir build && \
	cd build && \
	cmake .. && \
	make clean && \
	make all

CMD [ "build/ftsh" ]
