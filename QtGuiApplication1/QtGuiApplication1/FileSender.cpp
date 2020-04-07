#include "FileSender.h"
#include <fstream>
using namespace std;

void FilesSender::BeginSending()
{
	SingleFileSender fs,fs1;
	fs.fileName = "D:\\src";
	fs.fileExt = ".txt";
	fs.start();
	fs.wait();
	fs1.wait();
}

void SingleFileSender::run()
{
	const int RecDataSize = 255;
	WORD SockVersion = MAKEWORD(2, 2);
	WSADATA WsaData;
	int CheckWSA = WSAStartup(SockVersion, &WsaData);
	if (CheckWSA != 0)return;
		SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ClientSocket == INVALID_SOCKET)return;
		sockaddr_in ClientAddr;
		ClientAddr.sin_family = AF_INET;
		ClientAddr.sin_port = htons(8888);
		char IPdotdec[] = "192.168.18.3";
		inet_pton(AF_INET, IPdotdec, &ClientAddr.sin_addr.S_un);
		if (::connect(ClientSocket, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr)) == SOCKET_ERROR) 
		{
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}
		ifstream fp;
		fp.open(fileName + fileExt, ios::binary);
		fp.seekg(0, ios::end);
		int fileSize = fp.tellg();
		

		int CheckSend;
		unsigned char buffer[1024];
		int count = fileSize / 1024 + 1;

		int x = 3, beginPosition = 0;

		ifstream getLog;
		getLog.open(fileName + ".tmp");
		
		if (getLog.is_open())
		{
			getLog >> beginPosition;
			getLog.close();
		}
		string fullpath = fileName + fileExt;
		memcpy_s(&buffer[0], 4, &x, 4);
		memcpy_s(&buffer[4], 4, &fileSize, 4);
		memcpy_s(&buffer[8], 4, &beginPosition, 4);
		memcpy_s(&buffer[12], 1012, fullpath.c_str(), fullpath.length());
		const char* SendLength = (char*)buffer;
		fp.seekg(beginPosition * 1024L, ios::beg);

		CheckSend = send(ClientSocket, SendLength, 1024, 0);
		
		for (int i = beginPosition; i < count; i++)
		{
			fp.read((char*)buffer, 1024);
			const unsigned char* SendData = buffer;
			CheckSend = send(ClientSocket, (char*)SendData, fp.gcount(), 0);

			if (CheckSend == SOCKET_ERROR || isInterruptionRequested())
			{
				ofstream putLog;
				putLog.open(fileName + ".tmp");
				putLog << i - 1;
				putLog.close();
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
		}
		closesocket(ClientSocket);
		fp.close();
	WSACleanup();
	return ;
}