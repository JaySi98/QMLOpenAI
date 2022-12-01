#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QPair>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings();

    void init(QSharedPointer<QMap<const QString, const QVariant>> settings);
    void printAll();
    void save(const QString key, const QVariant& value);
    void save(QMap<const QString, const QVariant>& sett);
    QVariant load(QString key);

private:
    QSettings settings;
};

#endif // SETTINGS_H
