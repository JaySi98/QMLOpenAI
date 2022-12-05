#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{

}

Settings::~Settings()
{
    settings.sync();
}

void Settings::init(const QMap<QString, QVariant> values)
{
    if(settings.allKeys().length() == 0)
    {
        qInfo() << "Initalizing default application settings";
        save(values);
    }
    else
    {
        qInfo() << "Application settings are arleady initialised";
    }
}

void Settings::printAll()
{
    qInfo() << "All settings value: ";

    QStringList keys = settings.allKeys();
    foreach(QString key, keys)
    {
        qInfo() << "key: " << key << " = " << settings.value(key).toString();
    }
}

void Settings::save(const QString key, const QVariant &value)
{
    settings.setValue(key, value);
    qInfo() << settings.status();
}

void Settings::save(const QMap<QString, QVariant> &sett)
{
    QMapIterator<QString, QVariant> iter(sett);
    while (iter.hasNext())
    {
        iter.next();
        save(iter.key(), iter.value());
    }
}

QVariant Settings::load(QString key)
{
    if(!settings.contains(key))
    {
        qInfo() << "Settings dont contain: " + key + " value";
    }

    return settings.value(key);
}
