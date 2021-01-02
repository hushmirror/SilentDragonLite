// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef LOGCONTEXT_H
#define LOGCONTEXT_H

#include <string>
class LogContext
{
    public:
    virtual void log(std::string message) {};
};

#endif
