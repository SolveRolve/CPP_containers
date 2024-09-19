FROM quay.io/school21/alpine:3.16
WORKDIR /src
RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools \
	check-dev
RUN apk add --no-cache gtest gtest-dev openssl-dev gcovr && wget https://github.com/kinow/gtest-tap-listener/raw/master/src/tap.h -O /usr/include/gtest/tap.h

COPY /src /src