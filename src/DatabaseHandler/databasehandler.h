#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();
    void setAPIKey(const QString &apiKey);
    void signUserIn(const QString &emailAddress, const QString &password);

private:
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    QStringList headers;
    QString apiKey;
    QString idToken;

public slots:
    void replyNetworkReadyRead();
    void handleReply();
    void getReply(const QString &url, const QStringList &headers);

private slots:
    void performPOST(const QString &url, const QJsonDocument &payload);

signals:
    void replyReceived(const QByteArray &data, const QStringList &headers);
    void loginFailed();
    void loginSuccessful();
};

#endif // DATABASEHANDLER_H
