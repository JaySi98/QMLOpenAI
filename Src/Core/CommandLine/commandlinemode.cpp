#include <QDebug>
#include <QString>
#include "commandlinemode.h"
#include "commandparse.h"
#include "Src/Core/Settings/settings.h"

class ParameterNotSpecifiedException: public std::exception
{
public:
    ParameterNotSpecifiedException(char* message): message(message){}
    char* what()
    {
        return message;
    }

private:
    char* message;
};

QString getAPIKey();
QString getAIModel();
QString getRequest();

void CommandLineMode::run()
{
    qDebug() << "CommandLineMode::run() called";

    QString key;
    QString model;
    QString request;

    try
    {
        key = getAPIKey();
        model = getAIModel();
        request = getRequest();
    }
    catch(std::exception e)
    {
        qCritical() << "CommandLineMode::run() failed";
        return;
    }

    //TODO
}

QString getAPIKey()
{
    Settings settings;
    if(CommandLineParse::APIKeySet())
    {
        settings.save("key", CommandLineParse::APIKey());
        return CommandLineParse::APIKey();

    }
    else if(settings.load("key") != 0)
    {
        return settings.load("key").toString();
    }

    throw ParameterNotSpecifiedException((char*)"API key not specified");
}

QString getAIModel()
{
    if(CommandLineParse::APIKeySet())
    {
        return CommandLineParse::APIKey();
    }

    throw ParameterNotSpecifiedException((char*)"API key not specified");
}

QString getRequest()
{
    if(CommandLineParse::commandSet())
    {
        return CommandLineParse::requestedCommand();
    }

    throw ParameterNotSpecifiedException((char*)"Request not specified");
}
