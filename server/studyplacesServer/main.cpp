#include <QCoreApplication>
#include "mytcpserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;

    return a.exec();
}
