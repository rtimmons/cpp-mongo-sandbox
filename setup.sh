#!/usr/bin/env bash

set -eou pipefail
set -x

brew bundle

pushd "$(dirname "$0")" >/dev/null
    ROOT="$(pwd -P)"
popd > /dev/null

export LDFLAGS="-L$(brew --prefix openssl)/lib"
export CPPFLAGS="-I$(brew --prefix openssl)/include"

git submodule update --recursive --init

if [ ! -d build ]; then
    mkdir build
fi

pushd include/mongo-c-driver >/dev/null
    ./autogen.sh \
        --with-libbson=bundled \
        --disable-automatic-init-and-cleanup \
        --prefix="$ROOT/build"
popd >/dev/null

pushd build >/dev/null
    cmake ..
    make
    ../bin/mloader
popd >/dev/null
