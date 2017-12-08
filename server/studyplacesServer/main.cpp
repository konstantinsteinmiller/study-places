#include <QCoreApplication>
#include "mytcpserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
//    QString str("{ "uuid": "132rtasfhdij14uewjdfkldshf", "longitude": 12.4545,"latitude": 15.2323, "list": ["132r32312dsafsdasdfdfkldshf","asdfdf1123dsfgreg"], "total": 25}");


    return a.exec();
}
