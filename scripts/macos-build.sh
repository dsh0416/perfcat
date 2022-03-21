#!/bin/bash

bash scripts/macos-setup-codesign.sh
export MACOS_CERTID=frida-cert

export npm_config_runtime=electron
export npm_config_target=13.3.0
export npm_config_disturl=https://electronjs.org/headers

pushd frida
npm install --global add node-gyp
npm install --global prebuild
make node-macos NODE=$(which node)
popd

pushd fida-node
npm install
npm run prebuild -- -t 13.3.0 -r electron
popd
