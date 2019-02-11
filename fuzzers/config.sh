#!/bin/bash

# Default environment
DEFAULT_ENV="local"

# Working paths
DEFAULT_SRC="$(dirname $(dirname $(pwd)))"
DEFAULT_OUT="$(pwd)/out"
DEFAULT_WORK="$(pwd)"

# CFLAGS and LDFLAGS for local fuzzing
DEFAULT_CC="clang"
DEFAULT_CCLD=$DEFAULT_CC
DEFAULT_CFLAGS="-O1 -fno-omit-frame-pointer -g -ggdb3 -fsanitize=address,undefined -fsanitize-address-use-after-scope -fno-sanitize-recover=undefined -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
DEFAULT_LDFLAGS="-O1 -fno-omit-frame-pointer -g -ggdb3 -fsanitize=address,undefined -fno-sanitize-recover=undefined -fsanitize-address-use-after-scope"
COVERAGE_CFLAGS="-O1 -fno-omit-frame-pointer -g -ggdb3 -fprofile-instr-generate -fcoverage-mapping -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"
COVERAGE_LDFLAGS="-O1 -fno-omit-frame-pointer -g -ggdb3 -fprofile-instr-generate -fcoverage-mapping -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION"

# Janus configure flags
JANUS_CONF_FLAGS="--disable-docs --disable-post-processing --disable-turn-rest-api --disable-all-transports --disable-all-plugins --disable-all-handlers --disable-data-channels"

# Janus objects needed for fuzzing
JANUS_OBJECTS="janus-log.o janus-utils.o janus-rtcp.o janus-rtp.o"

# CFLAGS for fuzzer dependencies
DEPS_CFLAGS="$(pkg-config --static --cflags glib-2.0)"

# Libraries to link in with fuzzers
DEPS_LIB="-Wl,-Bstatic $(pkg-config --libs glib-2.0) -pthread -Wl,-Bdynamic"
