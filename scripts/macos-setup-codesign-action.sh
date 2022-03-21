#!/bin/bash

# This script is copied from https://github.com/llvm/llvm-project/blob/main/lldb/scripts/macos-setup-codesign.sh

CERT="frida-cert"

function error() {
    echo error: "$@" 1>&2
    exit 1
}

function cleanup {
    # Remove generated files
    rm -f "$DIR/$CERT.tmpl" "$DIR/$CERT.cer" "$DIR/$CERT.key" > /dev/null 2>&1
}

trap cleanup EXIT

# Create the certificate template
cat <<EOF >$DIR/$CERT.tmpl
[ req ]
default_bits       = 2048        # RSA key size
encrypt_key        = no          # Protect private key
default_md         = sha512      # MD to use
prompt             = no          # Prompt for DN
distinguished_name = codesign_dn # DN template
[ codesign_dn ]
commonName         = "$CERT"
[ codesign_reqext ]
keyUsage           = critical,digitalSignature
extendedKeyUsage   = critical,codeSigning
EOF

# Generate a new certificate
openssl req -new -newkey rsa:2048 -x509 -days 3650 -nodes -config "$DIR/$CERT.tmpl" -extensions codesign_reqext -batch -out "$DIR/$CERT.cer" -keyout "$DIR/$CERT.key" > /dev/null 2>&1
[ $? -eq 0 ] || error Something went wrong when generating the certificate

# Magic. Very dangerous.
sudo security authorizationdb write com.apple.trust-settings.admin allow

# Install the certificate in the system keychain
sudo security add-trusted-cert -r unspecified -p codeSign -k /Library/Keychains/System.keychain "$DIR/$CERT.cer"
sudo security import "$DIR/$CERT.key" -A -k /Library/Keychains/System.keychain

sudo pkill -f /usr/libexec/taskgated > /dev/null 2>&1

# Exit indicating the certificate is now generated and installed
exit 0
