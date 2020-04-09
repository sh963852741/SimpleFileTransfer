#pragma once
#include "QtGuiApplication1.h"
#include <QThread>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include<fstream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
Q_DECLARE_METATYPE(SOCKET);
class FilesReceiver :public QObject
{
	Q_OBJECT
public slots:
	void BeginListening();
	void SingleFileFinished();
	void ReceiveSingleFile(SOCKET socket);
private:
	bool ctnListen = true;
signals:
	void SingleFileGot();
};

class Listener :public QThread
{
	Q_OBJECT
public:
	void run();
signals:
	void IncommingFile(SOCKET socket);
};

class SingleFileReceiver : public QThread
{
	Q_OBJECT
public:
	string saveFlod;
	void run();
	SOCKET socket;
};