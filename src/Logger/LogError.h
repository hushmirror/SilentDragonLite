// Copyright 2019-2021 The Hush developers
// Released under the GPLv3
#ifndef LOGERROR_H
#define LOGERROR_H

#include "LogType.h"
#include "LogStrategy.h"
#include "LogWriter.h"

class LogError : public LogStrategy
{
    public:
        void log(std::string message)
        {
            LogWriter* lw = LogWriter::getInstance();
            lw->write(LogType::ERROR, message);
        }
};

#endif
