#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <QTimer>
#include <QWebSocketServer>
#include <QWebSocket>
#include "heatmap.h"

class MyWebServer : public QObject
{
    Q_OBJECT
public:
    explicit MyWebServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~MyWebServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

    QTimer *timer;
    HeatMap heatmap;
    QString heatmapstr;

public slots:

    void updateHeatMap();

};

#endif // MYTCPSERVER_H
