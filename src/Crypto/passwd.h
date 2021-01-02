// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef PASSWD_H
#define PASSWD_H
#include <stdio.h>
#include <sodium.h>
#include <QString>

class PASSWD
{
    public:
        static void show_hex_buff(unsigned char buf[]);
        static const unsigned char* key(QString);
};

#endif
