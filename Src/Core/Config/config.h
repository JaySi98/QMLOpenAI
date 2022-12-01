#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QVariant>
#include <QSharedPointer>

#define project_VERSION_MAJOR 1
#define project_VERSION_MINOR 0

#define ADD_OPENCV
#define ADD_BOOST
#define PROJECT_NAME "QML Template"
#define COMPANY_NAME "-"

QSharedPointer<QMap<const QString, const QVariant>> defaultSettings();

#endif // CONFIG_H
