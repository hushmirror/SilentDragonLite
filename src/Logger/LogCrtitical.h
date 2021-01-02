// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef LOGCRITICAL_H
#define LOGCRITICAL_H

#include "LogType.h"
#include "LogStrategy.h"
#include "LogWriter.h"

class LogCritical : public LogStrategy
{
    public:
        void log(std::string message)
        {
            LogWriter* lw = LogWriter::getInstance();
            lw->write(LogType::CRITICAL, message);
        }
};

#endif
