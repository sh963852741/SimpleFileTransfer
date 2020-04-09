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
	//fr->moveToThread(&receiveFiles);
	fr->BeginListening();
	fs->moveToThread(&sendFiles);
	sendFiles.start();
	//connect(ui.pushButton, &QPushButton::clicked, fr, &FilesReceiver::BeginListening);
	connect(ui.pushButton_2, &QPushButton::clicked, fr, &FilesReceiver::StopReceiving);
	//connect(ui.pushButton_2, &QPushButton::clicked, fr, &FilesReceiver::StopListening);
	connect(ui.pushButton_3, &QPushButton::clicked, fs, &FilesSender::BeginSending);
	//connect(&receiveFiles, &QThread::started, this, &QtGuiApplication1::ShowMsg);
	connect(fr, &FilesReceiver::SingleFileGot, this, &QtGuiApplication1::ShowMsg);
	receiveFiles.start();
	
}

QtGuiApplication1::~QtGuiApplication1()
{
	sendFiles.quit();
	receiveFiles.quit();
}

void QtGuiApplication1::CloseWindows()
{
	
	this->close();
}

void QtGuiApplication1::ShowMsg()
{
	ui.textEdit->insertPlainText("123");
}

void QtGuiApplication1::StopReceiving()
{
	
}
