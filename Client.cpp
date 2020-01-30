#include "Client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &Client::displayError);

    qDebug() << "connecting...";
    emit returnStatusConnect("connect");
    socket->connectToHost("jsonplaceholder.typicode.com", 80);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
        emit returnStatusConnect("Error " + socket->errorString());
    }
}
void Client::connected()
{
    qDebug() << "connected...";
    emit returnStatusConnect("write to server");

    socket->write("GET /users HTTP/1.0\nHOST: jsonplaceholder.typicode.com\n\n");
}

void Client::disconnected()
{
    qDebug() << "disconnected...";

    bool flagReturnJson = true;

    int indexRN = bufer.indexOf("\r\n");
    QString statusCodeHTTP = bufer.mid(0, indexRN); // HTTP/1.1 200 OK
    qDebug() << statusCodeHTTP;
    emit returnStatusConnect("connection closed " + statusCodeHTTP);

//    qDebug() << bufer;
    if (statusCodeHTTP.indexOf("200 OK") != -1)
    {
        int indexNN = bufer.indexOf("\r\n\r\n"); // индекс 2х переводов строки

        bufer.replace(0,indexNN + 4,"");
        QJsonDocument json_doc = QJsonDocument::fromJson(bufer.toUtf8());
        qDebug() << "is JSON? " << !json_doc.isNull();

        if (json_doc.isNull() == true){
            emit returnStatusConnect("this not JSON");
            flagReturnJson = false;
        } else {
            if (json_doc.array().at(0)["name"].isString() == false ||
                    json_doc.array().at(0)["address"]["geo"]["lat"].isString() == false)
            {
                qDebug() << "unexpected format JSON. missing fields Name, Lat";
                emit returnStatusConnect("unexpected format JSON");
                flagReturnJson = false;
            }
        }
    }
    if (flagReturnJson)
        emit returnJson(bufer);
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead()
{
    qDebug() << "reading...";

    bufer.append(socket->readAll());

}
void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << tr("Fortune Client"),
        qDebug() << tr("The host was not found. Please check the host name and port settings.");
        emit returnStatusConnect("The host was not found.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << tr("Fortune Client"),
        qDebug() << tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.");
        emit returnStatusConnect("Error The connection was refused by the peer.");
        break;
    default:
        qDebug() << tr("Fortune Client");
        qDebug() << tr("The following error occurred:");
        qDebug() << socket->errorString();
        emit returnStatusConnect("Error " + socket->errorString());
    }

}
