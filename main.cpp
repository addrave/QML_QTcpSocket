#include <QGuiApplication>
#include "maincl.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainCl *obj = new MainCl();

    return app.exec();
}
