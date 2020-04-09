#pragma once
#include <QThread>
#include <string>
#include<WinSock2.h>
#include<Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class FilesSender :public QObject
{
	Q_OBJECT
public slots:
	void BeginSending();
	void StopSending();
};

class SingleFileSender :public QThread
{
	Q_OBJECT
public:
	string fileName;
	string floderName;
public:
	void run();
};