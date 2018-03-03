#!/usr/bin/env bash

set -eou pipefail
set -x

brew bundle

export LDFLAGS="-L$(brew --prefix openssl)/lib"
export CPPFLAGS="-I$(brew --prefix openssl)/include"

git submodule update --recursive --init

pushd include/mongo-c-driver >/dev/null
    ./autogen.sh \
        --with-libbson=bundled \
        --disable-automatic-init-and-cleanup
popd >/dev/null

if [ ! -d build ]; then
    mkdir build
fi
pushd build >/dev/null
    cmake ..
    make
    ../bin/mloader
popd >/dev/null
