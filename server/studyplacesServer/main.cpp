#include <QCoreApplication>
#include "mytcpserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyWebServer server(10001,true);

    return a.exec();
}
