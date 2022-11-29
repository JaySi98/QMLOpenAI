#include "logger.h"

QString Logger::filename = QDir::currentPath() + QDir::separator() + "log.txt";
bool Logger::logging = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

Logger::Logger(QObject *parent): QObject(parent)
{

}

void Logger::atttach()
{
    Logger::logging = true;
    qInstallMessageHandler(Logger::handler);
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

        QFile logFile(Logger::filename);
        if(logFile.open(QIODevice::Append))
        {
            QTextStream stream(&logFile);
            stream << QDateTime::currentDateTime().toString() << " - " << text << context.file << " line: " << context.line;
            stream.flush();
            logFile.close();
        }
    }
    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
