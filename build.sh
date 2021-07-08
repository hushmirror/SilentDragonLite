#!/bin/bash
# Copyright 2019-2021 The Hush Developers

UNAME=$(uname)

if [ "$UNAME" == "Linux" ] ; then
    JOBS=2
elif [ "$UNAME" == "FreeBSD" ] ; then
    JOBS=$(nproc)
elif [ "$UNAME" == "Darwin" ] ; then
    JOBS=$(sysctl -n hw.ncpu)
else
    JOBS=1
fi

# check if rustc and cargo are installed, otherwise exit with error
if ! command -v rustc &> /dev/null
then
    echo "rustc could not be found. Please install it and try again."
    exit
fi
if ! command -v cargo &> /dev/null
then
    echo "cargo could not be found. Please install it and try again."
    exit
fi

VERSION=$(cat src/version.h |cut -d\" -f2)
echo "Compiling SilentDragonLite $VERSION with $JOBS threads..."
CONF=silentdragon-lite.pro

set -e
qbuild () {
   qmake $CONF CONFIG+=debug
   #lupdate $CONF
   #lrelease $CONF
   make -j$JOBS
}

if [ "$1" == "clean" ]; then
   make clean
elif [ "$1" == "linguist" ]; then
    lupdate $CONF
    lrelease $CONF
elif [ "$1" == "cleanbuild" ]; then
   make clean
   qbuild
else
   qbuild
fi
