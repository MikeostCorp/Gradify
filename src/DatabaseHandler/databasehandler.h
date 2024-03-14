#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    ~DatabaseHandler();

signals:

private:
    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;

public slots:
    void replyNetworkReadyRead();
    QByteArray getReply(const QString &url);
};

#endif // DATABASEHANDLER_H
