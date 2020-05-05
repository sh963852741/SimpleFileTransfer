#pragma once
#include <QtCore/QThread>
#include <QtCore/qthreadpool.h>
#include <string>
#include <QtCore/QRunnable>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#include"QtGuiApplication1.h"
#include <qdatetime.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class FilesSender :public QObject
{
	Q_OBJECT
public slots:
	void BeginSending(QString basepath, QStringList filename, QString IPaddress);
	void StopSending();
	void setcompress(bool a);
	void setencrypt(bool a);
	void process_compress(unsigned short id);
	void process_begin(unsigned short id);
	void process_process(unsigned short id, int value);
	void process_complete(unsigned short id, bool success, QString msg);
	void updatesendlog(QString basepath, QString filename, QTime time, QString mes);
private:
	QThreadPool sthreadpool;
	bool isencryption;
	bool iscompress;
signals:
	void rpt_process(unsigned short id, QString msg);
};

class SingleFileSender :public QObject, public QRunnable
{
	Q_OBJECT
public:
	static bool stop;
	bool iscompress;
	bool isencrypt;
	string ipAddress;
	string port;
	string fileName;
	string floderName;
	unsigned short seqID;
public:
	void run();
signals:
	void updatelog(QString basepath, QString filename, QTime time, QString mes);
	void compressing(unsigned id);
	void begin(unsigned short id);
	void process(unsigned short id, int value);
	void complete(unsigned short id, bool success, QString msg);
};
