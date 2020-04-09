#pragma once
#include "QtGuiApplication1.h"
#include <QThread>
#include <QThreadPool>
#include <QRunnable>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include<fstream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
Q_DECLARE_METATYPE(SOCKET);
class Listener :public QThread
{
	Q_OBJECT
public:
	void run();
signals:
	void IncommingFile(SOCKET socket);
};

class FilesReceiver :public QObject
{
	Q_OBJECT
public slots:
	void BeginListening();
	void StopListening();
	void SingleFileFinished();
	void ReceiveSingleFile(SOCKET socket);
	void StopReceiving();
private:
	Listener* listener=new Listener;
	QThreadPool threadpool;
signals:
	void SingleFileGot();
};

class SingleFileReceiver :public QObject, public QRunnable
{
	Q_OBJECT
public:
	static bool stop;
	string saveFlod;
	void run();
	SOCKET socket;
signals:
	void finished();
};