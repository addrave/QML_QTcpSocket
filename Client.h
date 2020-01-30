#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <string>
#include <iostream>
#include <QJsonDocument>

using namespace std;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void doConnect();

signals:
    void returnJson(QString);
    void returnStatusConnect(QString);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void displayError(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket *socket;
    QString bufer;

};

#endif // CLIENT_H
