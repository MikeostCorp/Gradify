#include "databasehandler.h"
#include <QDebug>
#include <QEventLoop>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QVariantMap>
#include <QSettings>
#include <QCoreApplication>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
    , apiKey{QString()}
{
    networkAccessManager = new QNetworkAccessManager(this);
}

DatabaseHandler::~DatabaseHandler()
{
    networkAccessManager->deleteLater();
}

void DatabaseHandler::setAPIKey(const QString &apiKey)
{
    this->apiKey = apiKey;
}

void DatabaseHandler::signUserIn(const QString &emailAddress, const QString &password)
{
    QString signInEndpoint
        = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + apiKey;

    QVariantMap variantPayload;
    variantPayload["email"] = emailAddress;
    variantPayload["password"] = password;
    variantPayload["returnSecureToken"] = true;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant(variantPayload);
    performPOST(signInEndpoint, jsonPayload);
}

void DatabaseHandler::replyNetworkReadyRead()
{
    QByteArray response = networkReply->readAll();
    qDebug() << QString(response);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    if (jsonDocument.object().contains("error")) {
        emit loginFailed();
    } else if (jsonDocument.object().contains("kind")) {
        idToken = jsonDocument.object().value("idToken").toString();
        emit loginSuccessful();
    }
}

void DatabaseHandler::getReply(const QString &tableName, const QStringList &headers)
{
    QSettings settingsConfig(QCoreApplication::applicationDirPath() + "/gradify.conf",
                             QSettings::IniFormat);
    QUrl urlLink(settingsConfig.value("url").toString());
    QString cleanedUrlStr = urlLink.toString(QUrl::StripTrailingSlash);

    this->headers = headers;

    QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(QUrl(cleanedUrlStr + tableName + ".json?auth=" + idToken)));
    connect(reply, &QNetworkReply::finished, this, &DatabaseHandler::handleReply);
}

void DatabaseHandler::performPOST(const QString &url, const QJsonDocument &payload)
{
    QNetworkRequest newRequest((QUrl(url)));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    networkReply = networkAccessManager->post(newRequest, payload.toJson());
    connect(networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::replyNetworkReadyRead);
}

void DatabaseHandler::handleReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit replyReceived(data, headers);
    } else {
        qDebug() << "Error occurred:" << reply->errorString();
    }
}
