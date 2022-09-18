#!/bin/bash

# setup package manager
git clone https://github.com/microsoft/vcpkg
if [[ "$OSTYPE" == "msys" ]]; then
  ./vcpkg/bootstrap-vcpkg.bat
else
  ./vcpkg/bootstrap-vcpkg.sh
fi

./vcpkg/bootstrap-vcpkg.sh

# install dependencies
./vcpkg/vcpkg install curl openssl
