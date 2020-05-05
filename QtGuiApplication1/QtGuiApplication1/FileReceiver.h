#pragma once
#include "QtGuiApplication1.h"
#include <QtCore/QThread>
#include <QtCore/QThreadPool>
#include <QtCore/QRunnable>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include<fstream>
#include <qdatetime.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
Q_DECLARE_METATYPE(SOCKET);
class Listener :public QThread
{
	Q_OBJECT
public:
	void run();
	string ipAddress;
	string port;
signals:
	void IncommingFile(SOCKET socket);
};

class FilesReceiver :public QObject
{
	Q_OBJECT
public:
	QString saveFlod;
public slots:
	void BeginListening(QString IPaddress);
	void StopListening();
	void process_Finished(unsigned short id, bool success, QString filePath);
	void process_Begin(QString filePath);
	void ReceiveSingleFile(SOCKET socket);
	void StopReceiving();
	void updateRecvFloder(QString floder);
	void BeginReceiving();
	void updaterevlog(QString floder, QString fliename, QTime time, QString mes);
private:
	Listener* listener = new Listener;
	QThreadPool threadpool;
	unsigned short recvCount = 0;
	bool islistening = false;
signals:
	void BeginRecvSingleFile(QString filePath, QTime time);
	void ReceiveFinished(unsigned short id, QString msg, QTime time);
};

class SingleFileReceiver :public QObject, public QRunnable
{                   
	Q_OBJECT
public:
	unsigned short seqID;
	static bool stop;
	string saveFlod;
	string filepath;
	void run();
	SOCKET socket;
signals:
	void updatelog(QString floder, QString fliename, QTime time, QString mes);
	void finished(unsigned short id, bool success, QString msg);
	void begin(QString filePath);
};