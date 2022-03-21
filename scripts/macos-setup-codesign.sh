#!/bin/bash

# This script is copied from https://github.com/llvm/llvm-project/blob/main/lldb/scripts/macos-setup-codesign.sh

TMP=$TMP
[[ -z "$TMP" ]] && TMP="/tmp"
CERT="frida-cert"

function error() {
    echo error: "$@" 1>&2
    exit 1
}

function cleanup {
    # Remove generated files
    rm -f "$TMP/$CERT.tmpl" "$TMP/$CERT.cer" "$TMP/$CERT.key" > /dev/null 2>&1
}

trap cleanup EXIT

# Check if the certificate is already present in the system keychain
security find-certificate -Z -p -c "$CERT" /Library/Keychains/System.keychain > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo Certificate has already been generated and installed
    exit 0
fi

# Create the certificate template
cat <<EOF >$TMP/$CERT.tmpl
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
openssl req -new -newkey rsa:2048 -x509 -days 3650 -nodes -config "$TMP/$CERT.tmpl" -extensions codesign_reqext -batch -out "$TMP/$CERT.cer" -keyout "$TMP/$CERT.key" > /dev/null 2>&1
[ $? -eq 0 ] || error Something went wrong when generating the certificate

# Install the certificate in the system keychain
sudo security add-trusted-cert -d -r trustRoot -p codeSign -k /Library/Keychains/System.keychain "$TMP/$CERT.cer" > /dev/null 2>&1
[ $? -eq 0 ] || error Something went wrong when installing the certificate

# Install the key for the certificate in the system keychain
sudo security import "$TMP/$CERT.key" -A -k /Library/Keychains/System.keychain > /dev/null 2>&1
[ $? -eq 0 ] || error Something went wrong when installing the key

# Kill task_for_pid access control daemon
sudo pkill -f /usr/libexec/taskgated > /dev/null 2>&1

# Exit indicating the certificate is now generated and installed
exit 0
