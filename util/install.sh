#!/bin/bash
# Copyright 2019-2021 The Hush Developers

./build.sh linguist && ./build.sh

username=$(id -un)

sed -i "s|\/home\/.*\/SilentDragonLite\/|\/home\/$username\/SilentDragonLite\/|g" SilentDragonLite.desktop

mv SilentDragonLite.desktop ~/.local/share/applications
# might be /usr/share/applications/ that requires sudo