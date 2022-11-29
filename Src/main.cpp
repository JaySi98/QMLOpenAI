#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Logger/logger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Logger logger;
    logger.atttach();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QMLTemplate/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}



// klasy nie muszą includowac loggera

//#include <QLoggingCategory>

//Q_DECLARE_LOGGING_CATEGORY(thing);
//Q_LOGGING_CATEGORY(thing, "thing");

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    Logger::atttach();

//    qInfo() << "dupa";
//    Test test;
//    test.testing();

//    //
//    qInfo(thing) << "eee";
//    QLoggingCategory::setFilterRules("thing.debug=false");
//    qDebug(thing) << "eee";

//    //
//    QLoggingCategory cat("cat");
//    cat.setEnabled(QtMsgType::QtDebugMsg,false);

//    return a.exec();
//}





//#include <QCoreApplication>
//#include <QSettings>
//#include <QRandomGenerator>

//void info(QSettings &settings)
//{
//    qDebug() << "File: " << settings.fileName();
//    qDebug() << "Keys: " << settings.allKeys();

//}

//void save(QSettings &settings)
//{
//    settings.setValue("test", 123);
//    qDebug() << settings.status();
//}

//void load(QSettings &settings)
//{
//    qDebug() << settings.value("test", 69);
//}

////
//void saveValueGroup(QSettings &settings,QString group, QString key, int value)
//{
//    settings.beginGroup(group);
//    settings.setValue(key, value);
//    settings.endGroup();
//}

//int getValueGroup(QSettings &settings, QString group, QString name)
//{
//    settings.beginGroup(group);
//    if(!settings.contains(name))
//    {
//        qDebug() << "does not contain";
//        settings.endGroup();
//        return 0;
//    }

//    int value = settings.value(name).toInt();
//    settings.endGroup();
//    return value;
//}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    QString filename = a.applicationDirPath() + "settings/ini";
//    QSettings settings(filename, QSettings::Format::IniFormat);

//    if(settings.allKeys().length() == 0)
//    {
//        qDebug() << "saving";
//        save(settings);
//    }
//    else
//    {
//        qDebug() << "loading";
//        load(settings);
//    }
//    info(settings);

//    //

//    saveValueGroup(settings, "group1", "value", 123);
//    saveValueGroup(settings, "group2", "value", 345);

//    qDebug() << getValueGroup(settings, "group1", "value");
//    qDebug() << getValueGroup(settings, "group2", "value");

//    //

//    QStringList people;
//    people << "A" << "B" << "C";
//    foreach(QString name, people)
//    {
//        int value  = QRandomGenerator::global()->bounded(100);
//        saveValueGroup(settings, "test", name, value);
//    }
//    // zapis do pliku
//    settings.sync();

//    foreach(QString group, settings.childGroups())
//    {
//        settings.beginGroup(group);
//        foreach(QString key, settings.childKeys())
//        {
//            qDebug() << "key:" << key << " = " << settings.value(key).toString();
//        }
//        settings.endGroup();
//    }

//    return a.exec();
//}
