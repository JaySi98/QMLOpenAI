#include "logger.h"

#define FILE_NAME "log.txt"

QString Logger::filename = QDir::currentPath() + QDir::separator() + FILE_NAME;
bool Logger::logging = false;
QFile Logger::logFile(Logger::filename);
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

Logger::Logger(QObject *parent): QObject(parent)
{

}

Logger::~Logger()
{
    qInfo() << "Closed: " << FILE_NAME;
    logFile.close();
}

void Logger::atttach()
{
    Logger::logging = true;
    qInstallMessageHandler(Logger::handler);

    if(logFile.open(QIODevice::Append))
    {
        qInfo() << "Opened: " << FILE_NAME;
    }
    else
    {
        qInfo() << "Failed to open: " << FILE_NAME;
    }
}

void Logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(Logger::logging)
    {
        QString text;

        switch(type)
        {
            case QtInfoMsg:     text = QString("Info: %1").arg(msg); break;
            case QtDebugMsg:    text = QString("Debug: %1").arg(msg);  break;
            case QtWarningMsg:  text = QString("Warning: %1").arg(msg); break;
            case QtCriticalMsg: text = QString("Critical: %1").arg(msg); break;
            case QtFatalMsg:    text = QString("Fatal: %1").arg(msg); break;
        }

        QTextStream stream(&logFile);
        stream << QDateTime::currentDateTime().toString() << " - " << text << " - " << QFileInfo(context.file).fileName() << " line: " << context.line << "\n";
        stream.flush();
    }
    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
