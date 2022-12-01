#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/Logger/logger.h"
#include "Core/Settings/settings.h"

void init(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Logger logger;
    logger.atttach();

    init(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QMLTemplate/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app,
                     [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}

void init(int argc, char *argv[])
{
    // TODO
    QCoreApplication::setOrganizationName(" ");
    QCoreApplication::setApplicationName(" ");

    Settings settings;
    settings.init();
}
