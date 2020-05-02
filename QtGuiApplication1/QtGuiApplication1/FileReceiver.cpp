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


		unsigned int fileLength;
		string fileName = (char*)&RevData[12];
		string fullPath = saveFlod + fileName;
		emit begin(QString::fromLocal8Bit(fullPath.c_str()));
		string tempfile = fullPath;
		tempfile.replace(tempfile.begin() + tempfile.find_last_of('.'), tempfile.end(), ".tmp");

		string comprefile = fullPath;
		comprefile.replace(comprefile.begin() + comprefile.find_last_of('.'), comprefile.end(), "Compre.tmp");
		
		memcpy_s(&fileLength, 4, &RevData[4], 4);
		unsigned int requestPosition;

		if (iscompress)
		{
			fullPath = comprefile;
		}

		fileWriter.open(fullPath, ios::_Nocreate | ios::binary);


		/*先判断文件是否需要断点续传*/
		if (fileWriter.is_open()) // 如果文件已经下载
		{
			ifstream readTmpFile;
			readTmpFile.open(tempfile);
			if (readTmpFile.is_open())readTmpFile >> requestPosition;
			else requestPosition = 0;
			readTmpFile.close();
		}
		else // 如果文件没有下载
		{
			if (access(fullPath.c_str(), 6) == -1)
			{
				for (int i = 0; i < fullPath.length(); ++i)
				{
					if (fullPath[i] == '\\')
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
		send(socket, (char*)&requestPosition, 4, 0);

		/*开始接收文件*/
		fileWriter.seekp(requestPosition, ios::beg);
		for (unsigned int i = requestPosition; i < fileLength;)
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
			if (stop || rev == SOCKET_ERROR || rev == 0)
			{
				/*记录当前下载进度*/
				ofstream writetemp;
				writetemp.open(tempfile, ios::trunc);
				writetemp << i;
				writetemp.close();
				fileWriter.close();
				closesocket(socket);
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
		md5.update(ifstream(saveFlod+fileName));
		string msg = md5.toString();
		send(socket, msg.c_str(), 33, 0);
		rev = recv(socket, (char*)RevData, 16, 0);
		if (strcmp((char*)RevData, "finish") == 0)
		{
			emit finished(seqID, true, "");
		}
		else
		{
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
	qRegisterMetaType<SOCKET>("SOCKET");
	connect(listener, &Listener::IncommingFile, this, &FilesReceiver::ReceiveSingleFile);
	//connect(listener, &Listener::finished, listener, &Listener::deleteLater);
	listener->ipAddress = IPaddress.mid(0, IPaddress.indexOf(":")).toLocal8Bit();
	listener->port = IPaddress.mid(IPaddress.indexOf(":") + 1).toLocal8Bit();
	listener->start();
}


void FilesReceiver::StopListening()
{
	listener->requestInterruption();
	listener->quit();
	listener->terminate();
}

void FilesReceiver::process_Finished(unsigned short id, bool success, QString filePath)
{
	emit ReceiveFinished(id, QString::fromLocal8Bit(success ? "传输完成" : "传输失败"));
}

void FilesReceiver::process_Begin(QString filePath)
{
	emit BeginRecvSingleFile(filePath);
}

void FilesReceiver::ReceiveSingleFile(SOCKET socket)
{
	SingleFileReceiver* fr = new SingleFileReceiver;
	fr->seqID = recvCount++;
	fr->saveFlod = this->saveFlod.toLocal8Bit();
	connect(fr, &SingleFileReceiver::begin, this, &FilesReceiver::process_Begin);
	connect(fr, &SingleFileReceiver::finished, this, &FilesReceiver::process_Finished);

	fr->socket = socket;
	threadpool.start(fr);
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
