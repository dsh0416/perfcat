#!/bin/bash

# install dependencies
if [[ "$OSTYPE" == "msys" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.bat
  ./vcpkg/vcpkg install curl openssl
  ./vcpkg/vcpkg install curl:x64-windows openssl:x64-windows
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.sh
  ./vcpkg/vcpkg install curl openssl
elif [[ "$OSTYPE" == "darwin"* ]]; then
  brew install curl openssl
  brew link --force openssl
fi
