#include "config.h"


QSharedPointer<QMap<const QString, const QVariant>> defaultSettings()
{
    QSharedPointer<QMap<const QString, const QVariant>> settings(new QMap<const QString, const QVariant>
    {

    });

    return settings;
}
