// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef LOGDEBUG_H
#define LOGDEBUG_H

#include "LogType.h"
#include "LogStrategy.h"
#include "LogWriter.h"

class LogDebug : public LogStrategy
{
    public:
        void log(std::string message)
        {
            LogWriter* lw = LogWriter::getInstance();
            lw->write(LogType::DEBUG, message);
        }
};

#endif
