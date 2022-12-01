#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QTextStream>
#include <iostream>

// otwieranie i zamykanie pliku w oddzielnych funkcjach żeby nie zajechac dysków
class Logger: public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();

    static void atttach();
    static void handler(QtMsgType type, const QMessageLogContext & context, const QString &msg);

    static bool logging;
    static QString filename;    
    static QFile logFile;
};

#endif // LOGGER_H
