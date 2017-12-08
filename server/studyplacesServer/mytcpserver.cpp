#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
           this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 10001))
    {
       std::cout << "Server could not start"<<std::endl;
    }
    else
    {
       std::cout << "Server started!"<<std::endl;
    }
    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateHeatMap()));
    timer->start(1000);

}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    std::cout<<"Got new Connection from "<<socket->peerAddress().toString().toStdString()<<std::endl;

    QByteArray Buffer;

    if(socket->waitForReadyRead(30000)){
        Buffer=socket->readAll();
        std::cout<<QString(Buffer).toStdString()<<std::endl;
    }
    socket->close();
}

void MyTcpServer::updateHeatMap()
{
    std::cout<<"Timer called"<<std::endl;
}
