#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/Logger/logger.h"
#include "Core/Settings/settings.h"
#include "Core/Config/config.h"
#include "Core/CommandLine/commandparse.h"
#include "Core/CommandLine/commandlinemode.h"

void init();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Logger logger;

    CommandLineParse::parse(app.arguments());
    logger.atttach();
    init();

    if(CommandLineParse::consoleVersion())
    {
        CommandLineMode::run();
    }
    else
    {
        QQmlApplicationEngine engine;
        const QUrl url(u"qrc:/OpenAI/main.qml"_qs);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app,
                         [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);

        }, Qt::QueuedConnection);

        engine.load(url);
        return app.exec();
    }

    return EXIT_SUCCESS;
}

void init()
{
    QCoreApplication::setOrganizationName(PROJECT_NAME);
    QCoreApplication::setApplicationName(COMPANY_NAME);

    const QMap<QString, QVariant> values =
    {
//        QPair<QString, QVariant>{"value", 100},
    };

    Settings settings;
    settings.init(values);
}
