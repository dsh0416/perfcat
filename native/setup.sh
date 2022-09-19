#!/bin/bash

# install dependencies
if [[ "$OSTYPE" == "msys" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.bat
  ./vcpkg/vcpkg install -y curl openssl
  ./vcpkg/vcpkg install -y curl:x64-windows openssl:x64-windows
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.sh
  ./vcpkg/vcpkg install -y curl openssl
elif [[ "$OSTYPE" == "darwin"* ]]; then
  brew install curl openssl
  brew link --force openssl
fi
