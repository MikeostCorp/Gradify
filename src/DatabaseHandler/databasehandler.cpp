#include "databasehandler.h"
#include <QEventLoop>
#include <QDebug>
#include <QNetworkRequest>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
}

DatabaseHandler::~DatabaseHandler()
{
    networkManager->deleteLater();
}

void DatabaseHandler::replyNetworkReadyRead()
{
    qDebug() << QString(networkReply->readAll());
}

QByteArray DatabaseHandler::getReply(const QString &url)
{
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(url)));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    reply->deleteLater();
    return data;
}
