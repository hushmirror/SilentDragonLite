#!/bin/bash
# Copyright 2019-2021 The Hush Developers

username=$(id -un)
sed -i "s|\/home\/.*\/SilentDragonLite\/|\/home\/$username\/SilentDragonLite\/|g" SilentDragonLite.desktop
cp SilentDragonLite.desktop ~/.local/share/applications
