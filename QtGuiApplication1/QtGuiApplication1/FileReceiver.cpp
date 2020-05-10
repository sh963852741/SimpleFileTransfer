#include "FileReceiver.h"
#include"compre.h"
#include <direct.h>
#include <io.h>
bool SingleFileReceiver::stop = false;
void SingleFileReceiver::run()
{
	unsigned char RevData[1024];
	ofstream fileWriter;

	int rev = recv(socket, (char*)RevData, 1024, 0);
	int type;
	bool iscompress;
	bool isencrypt;
	if (rev > 0)
	{
		memcpy_s(&type, 4, &RevData[0], 4);
		type = type & 0x000000ff;
		if (type == 1)
		{
			isencrypt = true;
			iscompress = false;
		}
		if (type == 2)
		{
			isencrypt = true;
			iscompress = true;
		}
		if (type == 3)
		{
			isencrypt = false;
			iscompress = false;
		}
		if (type == 4)
		{
			isencrypt = false;
			iscompress = true;
		}

		if (isencrypt)
		{
			for (int i = 0; i < 1024; i++)
			{
				RevData[i] += 4;
			}
		}


		unsigned long long int fileLength;
		
		string fileName = (char*)&RevData[20];
		filepath = fileName;
		string fullPath = saveFlod + fileName;
		emit begin(QString::fromLocal8Bit(fullPath.c_str()));
		string tempfile = fullPath;
		tempfile.append(".tmp");
		//tempfile.replace(tempfile.begin() + tempfile.find_last_of('.'), tempfile.end(), ".tmp");

		string comprefile = fullPath;
		comprefile.append(".Compare.tmp");
		//comprefile.replace(comprefile.begin() + comprefile.find_last_of('.'), comprefile.end(), "Compre.tmp");
		
		memcpy_s(&fileLength, 8, &RevData[4], 8);
		unsigned long long int requestPosition;

		if (iscompress)
		{
			fullPath = comprefile;
		}

		fileWriter.open(fullPath, ios::_Nocreate | ios::binary);


		/*先判断文件是否需要断点续传*/
		if (fileWriter.is_open()) // 如果文件已经下载
		{
			//判断是否已经传输完成
			QFileInfo fileInfo(QString::fromLocal8Bit(tempfile.c_str()));
			if (fileInfo.isFile())
			{
				ifstream readTmpFile;
				readTmpFile.open(tempfile);
				if (readTmpFile.is_open())readTmpFile >> requestPosition;
				else requestPosition = 0;
				readTmpFile.close();
			}
			else
			{
				requestPosition =fileLength;
			}
		}
		else // 如果文件没有下载
		{
			if (access(fullPath.c_str(), 6) == -1)
			{
				for (int i = 0; i < fullPath.length(); ++i)
				{
					if (fullPath[i] == '\\' || fullPath[i] == '/')
					{
						string temp = fullPath.substr(0, i);
						if (access(temp.c_str(), 0) == -1)
						{
							mkdir(temp.c_str());
						}
					}
				}
			}
			fileWriter.open(fullPath, ios::app | ios::binary);
			fileWriter.seekp(fileLength, ios::beg);
			requestPosition = 0;
		}

		/*请求客户端从指定位置开始发送文件*/
		send(socket, (char*)&requestPosition, 8, 0);

		/*开始接收文件*/
		fileWriter.seekp(requestPosition, ios::beg);
		for (unsigned long long int i = requestPosition; i < fileLength;)
		{
			rev = recv(socket, (char*)RevData, 1024, 0);
			if (isencrypt)
			{
				for (int i = 0; i < 1024; i++)
				{
					RevData[i] += 4;
				}
			}
			/* 如果传输中断 */
			if (stop || rev == SOCKET_ERROR || rev <= 0)
			{
				/*记录当前下载进度*/
				ofstream writetemp;
				writetemp.open(tempfile, ios::trunc);
				writetemp << i;
				writetemp.close();
				fileWriter.close();
				closesocket(socket);
				emit emit updatelog(QString::fromLocal8Bit(saveFlod.c_str()), QString::fromLocal8Bit(fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("接收中断"));
				emit finished(seqID, false, QString::fromLocal8Bit("传输中断"));
				return;
			}

			i += rev;
			fileWriter.write((char*)RevData, rev);
		}
		fileWriter.close();
		if (iscompress)
		{
			inf(fullPath, saveFlod + fileName);
			QString str = QString::fromLocal8Bit(fullPath.c_str());
			QFile::remove(str);
		}
		MD5 md5;
		md5.update(ifstream(saveFlod+fileName, ios::binary));
		string msg = md5.toString();
		send(socket, msg.c_str(), 33, 0);
		rev = recv(socket, (char*)RevData, 16, 0);
		if (strcmp((char*)RevData, "finish") == 0)
		{
			//传输完成删除tmp文件
			QString str = QString::fromLocal8Bit(tempfile.c_str());
			QFile::remove(str);
			emit emit updatelog(QString::fromLocal8Bit(saveFlod.c_str()), QString::fromLocal8Bit(fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("接收成功"));
			emit finished(seqID, true, "");
		}
		else
		{
			emit emit updatelog(QString::fromLocal8Bit(saveFlod.c_str()), QString::fromLocal8Bit(fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("接收失败"));
			emit finished(seqID, false, "");
		}
		closesocket(socket);
	}
}
void Listener::run()
{
	const int DataSize = 255;
	WORD SockVertion = MAKEWORD(2, 2);
	WSADATA WsaData;
	int CheckWSA = WSAStartup(SockVertion, &WsaData);
	if (CheckWSA != 0) return;
	SOCKET SeverListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SeverListen == INVALID_SOCKET)return;
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(port.c_str()));
	//sin.sin_port = htons(10000);
	const char* IPdotdec = ipAddress.c_str();
	//sin.sin_addr.S_un.S_addr = INADDR_ANY;
	sin.sin_addr.S_un.S_addr = inet_addr(IPdotdec);
	if (::bind(SeverListen, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)return;
	if (listen(SeverListen, 5) == SOCKET_ERROR)return;

	SOCKET ClientSocket;
	sockaddr_in RemoteAddr;
	int RemoteAddrSize = sizeof(RemoteAddr);
	/*err = fopen_s(&fp, "D:\\result.txt", "w");
	if (err != 0) return;*/

	while (!isInterruptionRequested())
	{
		ClientSocket = accept(SeverListen, (SOCKADDR*)&RemoteAddr, &RemoteAddrSize);
		if (ClientSocket != INVALID_SOCKET)
		{
			emit IncommingFile(ClientSocket);
			//break;
		}
	}
}

void FilesReceiver::BeginListening(QString IPaddress)
{
	if (!islistening)
	{
		islistening = true;
		qRegisterMetaType<SOCKET>("SOCKET");
		connect(listener, &Listener::IncommingFile, this, &FilesReceiver::ReceiveSingleFile);
		//connect(listener, &Listener::finished, listener, &Listener::deleteLater);
		listener->ipAddress = IPaddress.mid(0, IPaddress.indexOf(":")).toLocal8Bit();
		listener->port = IPaddress.mid(IPaddress.indexOf(":") + 1).toLocal8Bit();
		listener->start();
	}
}


void FilesReceiver::StopListening()
{
	listener->requestInterruption();
	listener->quit();
	listener->terminate();
}

void FilesReceiver::process_Finished(unsigned short id, bool success, QString filePath)
{
	emit ReceiveFinished(id, QString::fromLocal8Bit(success ? "传输完成" : "传输失败"), QTime::currentTime());
}

void FilesReceiver::process_Begin(QString filePath)
{
	emit BeginRecvSingleFile(filePath, QTime::currentTime());
}

void FilesReceiver::ReceiveSingleFile(SOCKET socket)
{
	SingleFileReceiver* fr = new SingleFileReceiver;
	fr->seqID = recvCount++;
	fr->saveFlod = this->saveFlod.toLocal8Bit();
	connect(fr, &SingleFileReceiver::begin, this, &FilesReceiver::process_Begin);
	connect(fr, &SingleFileReceiver::finished, this, &FilesReceiver::process_Finished);
	connect(fr, &SingleFileReceiver::updatelog, this, &FilesReceiver::updaterevlog);
	fr->socket = socket;
	if (SingleFileReceiver::stop) closesocket(socket);
	else threadpool.start(fr);
}

void FilesReceiver::StopReceiving()
{
	SingleFileReceiver::stop = true;
	threadpool.clear();
	threadpool.waitForDone();
}

void FilesReceiver::BeginReceiving()
{
	SingleFileReceiver::stop = false;
}

void FilesReceiver::updateRecvFloder(QString floder)
{
	this->saveFlod = floder;
}

void FilesReceiver::updaterevlog(QString floder, QString filename, QTime time, QString mes)
{
	ofstream output;
	output.open("receivelog.csv", ios::app);
	string nowtime = time.toString("h:m:s").toLocal8Bit();
	string flodername = floder.toLocal8Bit();
	string file = filename.toLocal8Bit();
	string message = mes.toLocal8Bit();
	output << nowtime << "," << flodername << "," << file << "," << message << '\n';
	output.close();
}