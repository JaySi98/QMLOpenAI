#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
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

    static void atttach();
    static void handler(QtMsgType type, const QMessageLogContext & context, const QString &msg);

    static bool logging;
    static QString filename;
};

#endif // LOGGER_H
