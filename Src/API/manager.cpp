#include "manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent},
      manager(QNetworkAccessManager())
{
    data.clear();
    status = STATUS_NONE;
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Manager::SSLError);
}

void Manager::sendRequest(QNetworkRequest request)
{
    QNetworkReply* reply = manager.get(request);

    connect(reply, &QNetworkReply::finished,      this, &Manager::replyFinished);
    connect(reply, &QNetworkReply::readyRead,     this, &Manager::ReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &Manager::ReplyError);
}

void Manager::ReadyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    data.append(reply->readAll());
    status = STATUS_OK;
}

void Manager::SSLError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    status = STATUS_ERROR;
    for (const QSslError &error : errors)
    {
        qCritical() << error.errorString();
    }

    reply->ignoreSslErrors();
}

void Manager::ReplyError(QNetworkReply::NetworkError errorCode)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QNetworkReply::NetworkError error = reply->error();

    if (error != QNetworkReply::NoError)
    {
        qCritical() << reply->errorString();
        status = STATUS_ERROR;
    }
}

void Manager::replyFinished()
{
    if(status == STATUS_OK)
    {
        qDebug() << data;
    }
    else
    {
        qCritical() << "Failed to get the response";
    }

    data.clear();
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}
