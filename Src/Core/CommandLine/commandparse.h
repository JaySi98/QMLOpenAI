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
        CommandAPIKeySet      = 0x04,
        CommandModelSet       = 0x08,
        CommandRequestSet     = 0x10,
    };

    int  parse(QStringList arguments);
    bool consoleVersion();

    bool APIKeySet();
    bool modelSet();
    bool commandSet();
    QString APIKey();
    QString AImodel();
    QString requestedCommand();
}

#endif // COMMANDPARSE_H
