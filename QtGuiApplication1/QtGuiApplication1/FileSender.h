#pragma once
#include <QThread>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

class FilesSender :public QObject
{
	Q_OBJECT
public slots:
	void BeginSending();
};

class SingleFileSender :public QThread
{
	Q_OBJECT
public:
	void run();
};