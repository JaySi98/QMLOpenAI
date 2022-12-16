#ifndef COMMANDPARSE_H
#define COMMANDPARSE_H

#include <QStringList>
#include <QCommandLineParser>
#include <QCommandLineOption>

namespace CommandLineParse
{
    enum Result
    {
        CommandOk             = 0x00,
        CommandError          = 0x01,
        CommandConsoleVersion = 0x02,
    };

    int  parse(QStringList arguments);
    bool consoleVersion();
}

#endif // COMMANDPARSE_H
