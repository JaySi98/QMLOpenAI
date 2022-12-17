#include <QStringList>
#include "Src/Core/Config/config.h"
#include "commandparse.h"

#define MIN_NUMB_ARGUMENTS 0

static int parseResult = CommandLineParse::Result::CommandOk;
static QString apiKey  = QString();
static QString model   = QString();
static QString request = QString();

int CommandLineParse::parse(QStringList arguments)
{
    if(arguments.count() > MIN_NUMB_ARGUMENTS)
    {
        QCommandLineParser parser;
        parser.setApplicationDescription(PROJECT_NAME);
        parser.addHelpOption();
        parser.addVersionOption();

        QCommandLineOption consoleOption(QStringList() << "c" << "console",
            QCoreApplication::translate("main", "runs console version of the program"));
        parser.addOption(consoleOption);

        QCommandLineOption keyOption(QStringList() << "k" << "key",
                QCoreApplication::translate("main", "holds the API key required to send requests"),
                QCoreApplication::translate("main", "OpenAI API key"));
        parser.addOption(keyOption);

        QCommandLineOption modelOption(QStringList() << "m" << "model",
                QCoreApplication::translate("main", "holds the API key required to send requests"),
                QCoreApplication::translate("main", "OpenAI model"));
        parser.addOption(modelOption);

        QCommandLineOption commandOption(QStringList() << "r" << "request",
                QCoreApplication::translate("main", "Request to be procedded"),
                QCoreApplication::translate("main", "request"));
        parser.addOption(commandOption);

        if (!parser.parse(arguments))
        {
            qWarning() << parser.errorText();
            parseResult = CommandError;
        }

        if(parser.isSet(consoleOption))
        {
            qDebug() << "Console mode selected";
            parseResult |= CommandConsoleVersion;
        }

        if(parser.isSet(keyOption))
        {
            parseResult |= CommandAPIKeySet;
            apiKey = parser.value(keyOption);
            qDebug() << "API key set: " << apiKey;
        }

        if(parser.isSet(modelOption))
        {
            parseResult |= CommandModelSet;
            model = parser.value(modelOption);
            qDebug() << "Model set: " << model;
        }

        if(parser.isSet(commandOption))
        {
            parseResult |= CommandRequestSet;
            request = parser.value(commandOption);
            qDebug() << "Request set: " << request;
        }
    }

    return parseResult;
}

bool CommandLineParse::consoleVersion()
{
    return (parseResult & CommandConsoleVersion) ? true : false;
}

bool CommandLineParse::modelSet()
{
    return (parseResult & CommandModelSet) ? true : false;
}

bool CommandLineParse::APIKeySet()
{
    return (parseResult & CommandAPIKeySet) ? true : false;
}

bool CommandLineParse::commandSet()
{
    return (parseResult & CommandRequestSet) ? true : false;
}

QString CommandLineParse::APIKey()
{
    return apiKey;
}

QString CommandLineParse::AImodel()
{
    return model;
}

QString CommandLineParse::requestedCommand()
{
    return request;
}
