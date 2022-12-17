#include <QDebug>
#include <QString>
#include "commandlinemode.h"

QString getAPIKey();
QString getAIModel();
QString getRequest();

void CommandLineMode::run()
{
    qDebug() << "CommandLineMode::run() called";

    try
    {

    }
    catch(...)
    {
        qDebug() << "CommandLineMode::run() failed";
        return;
    }

    //TODO
}

QString getAPIKey()
{
    QString key;

    //TODO
    return key;
}

QString getAIModel()
{
    QString model;

    //TODO
    return model;
}

QString getRequest()
{
    QString request;

    //TODO
    return request;
}
