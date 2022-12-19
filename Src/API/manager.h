#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <QUrl>
#include <QAuthenticator>

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

public slots:
    void sendRequest(QNetworkRequest request);

private:

    typedef enum
    {
        STATUS_NONE,
        STATUS_OK,
        STATUS_ERROR,
    }requestStatus;

    QNetworkAccessManager manager;
    QByteArray data;
    requestStatus status;

private slots:
    void ReadyRead();
    void SSLError(QNetworkReply* reply, const QList<QSslError> &errors);
    void ReplyError(QNetworkReply::NetworkError errorCode);
    void replyFinished();

signals:
};

#endif // MANAGER_H
