#ifndef MAINCL_H
#define MAINCL_H

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "Client.h"


class MainCl : public QObject
{
    Q_OBJECT
public:
    MainCl();

public slots:
    void receiveJson(QString);
    void receiveStatusConnect(QString);

private:
    QQuickView *view;
    Client *client;
};

#endif // MAINCL_H
