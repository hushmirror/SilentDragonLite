#!/bin/bash
# Copyright 2019-2021 The Hush developers
# Released under the GPLv3
VERSION=1.0.18

# First thing to do is see if libsodium.a exists in the res folder. If it does, then there's nothing to do
if [ -f res/libsodium.a ]; then
    echo "libsodium $VERSION is already built! Nothing to do"
    exit 0
fi

echo "Building libsodium $VERSION"

# Go into the lib sodium directory
cd res/libsodium
if [ ! -f libsodium-1.0.18.tar.gz ]; then
    echo "Downloading libsodium $VERSION"
    curl -LO https://github.com/MyHush/libsodium/releases/download/1.0.18/libsodium-1.0.18.tar.gz
fi

if [ ! -f libsodium-1.0.18.tar.gz ]; then
    echo "Unable to download libsodium $VERSION !!! Aborting"
    exit 1
fi

if [ ! -d libsodium-1.0.18 ]; then
    echo "Unpacking libsodium $VERSION"
    tar xf libsodium-1.0.18.tar.gz
fi

if [ ! -d libsodium-1.0.18 ]; then
    echo "Unable to unpack libsodium $VERSION !!! Aborting"
    exit 1
fi

# Now build it
cd libsodium-1.0.18
echo "Configuring libsodium $VERSION"
LIBS="" ./configure
make clean

echo "Compiling libsodium $VERSION"
if [[ "$OSTYPE" == "darwin"* ]]; then
    make CFLAGS="-mmacosx-version-min=10.11" CPPFLAGS="-mmacosx-version-min=10.11" -j4
else
    make -j8
fi
cd ..

if [ ! -e libsodium-1.0.18/src/libsodium/.libs/libsodium.a ]; then
    echo "Unable to compile libsodium $VERSION !!! Aborting"
    exit 1
fi

# copy the library to the parents's res/ folder
cp libsodium-1.0.18/src/libsodium/.libs/libsodium.a ../
