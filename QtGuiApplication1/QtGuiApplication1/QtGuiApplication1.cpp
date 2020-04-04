#include "QtGuiApplication1.h"
#include "FileReceiver.h"
#include "FileSender.h"
#include<WinSock2.h>
#include<Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	FilesReceiver* fr = new FilesReceiver;
	FilesSender* fs = new FilesSender;
	//fr->setParent(this);
	//fs->setParent(this);
	fr->moveToThread(&receiveFiles);
	fs->moveToThread(&sendFiles);
	connect(ui.pushButton, &QPushButton::clicked, fr, &FilesReceiver::BeginListening);
	//connect(ui.pushButton_2, &QPushButton::clicked, this, &QtGuiApplication1::StopListening);
	connect(ui.pushButton_3, &QPushButton::clicked, fs, &FilesSender::BeginSending);
	//connect(&receiveFiles, &QThread::started, this, &QtGuiApplication1::ShowMsg);
	connect(fr, &FilesReceiver::SingleFileGot, this, &QtGuiApplication1::ShowMsg);
	receiveFiles.start();
	sendFiles.start();
}

void QtGuiApplication1::CloseWindows()
{
	
	this->close();
}

void QtGuiApplication1::ShowMsg()
{
	ui.textEdit->insertPlainText("123");
}

void QtGuiApplication1::StopListening()
{
	receiveFiles.terminate();
	//receiveFiles.quit();
	receiveFiles.wait();
}
