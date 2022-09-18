#!/bin/bash

# install dependencies
if [[ "$OSTYPE" == "msys" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.bat
  ./vcpkg/vcpkg install curl openssl
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.sh
  ./vcpkg/vcpkg install curl openssl
elif [[ "$OSTYPE" == "darwin"* ]]; then
  brew install curl openssl
  brew link --force openssl
  pkg-config --modversion openssl
fi
