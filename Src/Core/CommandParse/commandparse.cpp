#include <QStringList>
#include "Src/Core/Config/config.h"
#include "commandparse.h"

#define MIN_NUMB_ARGUMENTS 0

static int parseResult = CommandLineParse::Result::CommandOk;

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

        if (!parser.parse(arguments))
        {
            qWarning() << parser.errorText();
            parseResult = CommandError;
        }

        if(parser.isSet(consoleOption))
        {
            qDebug() << "console detected";
            parseResult |= CommandConsoleVersion;
        }
    }

    return parseResult;
}

bool CommandLineParse::consoleVersion()
{
    return (parseResult & CommandConsoleVersion) ? true : false;
}
