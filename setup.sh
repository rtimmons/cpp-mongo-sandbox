#!/usr/bin/env bash

set -eou pipefail
set -x

brew bundle

export LDFLAGS="-L/usr/local/opt/openssl/lib"
export CPPFLAGS="-I/usr/local/opt/openssl/include"

git submodule update --init

