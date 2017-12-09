#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <QTimer>
#include "heatmap.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
    void updateHeatMap();

private:
    QTcpServer *server;
    QTimer *timer;
    HeatMap heatmap;
    QString heatmapstr;
};

#endif // MYTCPSERVER_H
