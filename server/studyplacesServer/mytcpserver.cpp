#include "mytcpserver.h"

MyWebServer::MyWebServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
	if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Server listening on port" << port;
    	connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &MyWebServer::onNewConnection);
    	connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &MyWebServer::closed);
    }

    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateHeatMap()));
    timer->start(60000);
    heatmapstr=heatmap.getStr();
}

MyWebServer::~MyWebServer(){
	m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void MyWebServer::onNewConnection()
{
    // need to grab the socket
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &MyWebServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &MyWebServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &MyWebServer::socketDisconnected);

    m_clients << pSocket;

    std::cout<<"\n\n\nGot new Connection from "<<pSocket->peerAddress().toString().toStdString()<<std::endl;

}

void MyWebServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

	std::cout<<"got message "<<message.toStdString()<<std::endl;

	if(message.at(0)=='{')
	{
		heatmap.addData(message);
	
		std::cout<<"send "<<heatmapstr.toStdString()<<std::endl;
	 	
		if (pClient) {
        	pClient->sendTextMessage(heatmapstr);
    		}
	}
}

void MyWebServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void MyWebServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void MyWebServer::updateHeatMap()
{
    std::cout<<"calculating new heatmap"<<std::endl;
    heatmapstr=heatmap.getStr();
    heatmap.reset();
}
