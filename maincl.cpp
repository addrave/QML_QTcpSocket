#include "maincl.h"

MainCl::MainCl() :
    QObject()
{
    view = new QQuickView();
    view->setSource(QUrl("qrc:/Test4.qml"));
    view->show();
    client = new Client; // TCP request
    connect(client, SIGNAL(returnJson(QString)),this, SLOT(receiveJson(QString)));
    connect(client, SIGNAL(returnStatusConnect(QString)),this, SLOT(receiveStatusConnect(QString)));
    client->doConnect();
}

void MainCl::receiveJson(QString arg)
{
//    qDebug() << arg;
    view->rootContext()->setContextProperty("contextJson", arg);
}
void MainCl::receiveStatusConnect(QString arg)
{
    qDebug() << arg << "!!!!!!!!!!!!!!!!!";
    view->rootContext()->setContextProperty("contextStatusText", arg);
}
