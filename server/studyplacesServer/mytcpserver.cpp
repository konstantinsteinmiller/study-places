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
    heatmapstr=heatmap.getStr();

}

void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    std::cout<<"\n\n\nGot new Connection from "<<socket->peerAddress().toString().toStdString()<<std::endl;

    QString Buffer;
    if(socket->waitForReadyRead(20000)){
        Buffer=socket->readAll();
        std::cout<<"received Data: "<<Buffer.toStdString()<<std::endl;
        if(Buffer.at(0)=="{"){
            heatmap.addData(Buffer);
        }
        else if(Buffer.at(0)=="r"){
            std::cout<<"sending "<<heatmapstr.toStdString()<<" to client "<<socket->peerAddress().toString().toStdString()<<std::endl;
            socket->write(heatmapstr.toLocal8Bit());
            socket->waitForBytesWritten(1000);
        }
    }
    socket->close();
}

void MyTcpServer::updateHeatMap()
{
    heatmapstr=heatmap.getStr();
    heatmap.reset();
}
