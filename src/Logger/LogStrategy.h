// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef LOGSTRATEGY_H
#define LOGSTRATEGY_H

#include <string>
class LogStrategy
{
    public:
    virtual void log(std::string message) {};
};

#endif
