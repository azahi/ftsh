FROM alpine:3.11.3

LABEL maintainer "Azat Bahawi <azahi@teknik.io>"

RUN apk -U upgrade \
 && apk add build-base cmake

COPY . /tmp/minishell

RUN cmake -S /tmp/minishell -B /tmp/minishell -DCMAKE_BUILD_TYPE=Release \
 && cmake --build /tmp/minishell --target all -j $(getconf _NPROCESSORS_CONF) --target all \
 && strip -s /tmp/minishell/minishell \
 && cp /tmp/minishell/minishell /bin \
 && apk del build-base cmake \
 && rm -rf /var/cache/apk/*

ENV USER=user \
    HOST=host

CMD [ "minishell" ]
