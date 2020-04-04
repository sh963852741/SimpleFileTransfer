#include "FileReceiver.h"

void SingleFileReceiver::run()
{
	const int DataSize = 255;
	unsigned char RevData[DataSize + 1];
	ofstream fileWriter;
	fileWriter.open(R"(D:\FileTransfer\src.txt)",ios::binary);
	while (1)
	{
		int rev = recv(socket, (char*)RevData, DataSize, 0);
		if (rev > 0) {
			RevData[rev] = '\0';
			int RevLength;
			sscanf_s((char*)RevData, "%d", &RevLength);
			for (int i = 0; i < RevLength; i++) {
				rev = recv(socket, (char*)RevData, DataSize, 0);
				fileWriter.write((char*)RevData, 255);
			}
			fileWriter.close();
			break;
		}
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
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(SeverListen, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)return;
	if (listen(SeverListen, 5) == SOCKET_ERROR)return;

	SOCKET ClientSocket;
	sockaddr_in RemoteAddr;
	int RemoteAddrSize = sizeof(RemoteAddr);
	char RevData[DataSize + 1];
	FILE* fp = NULL;
	errno_t err = 0;
	/*err = fopen_s(&fp, "D:\\result.txt", "w");
	if (err != 0) return;*/
	SingleFileReceiver fr;

	while (1)
	{
		ClientSocket = accept(SeverListen, (SOCKADDR*)&RemoteAddr, &RemoteAddrSize);
		if (ClientSocket != INVALID_SOCKET)
		{
			emit IncommingFile(ClientSocket);
			//break;
		}
	}
}
void FilesReceiver::BeginListening()
{
	Listener* listener = new Listener;
	qRegisterMetaType<SOCKET>("SOCKET");
	connect(listener, &Listener::IncommingFile, this, &FilesReceiver::ReceiveSingleFile);
	listener->start();
//
//	const int DataSize = 255;
//	WORD SockVertion = MAKEWORD(2, 2);
//	WSADATA WsaData;
//	int CheckWSA = WSAStartup(SockVertion, &WsaData);
//	if (CheckWSA != 0) return;
//	SOCKET SeverListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (SeverListen == INVALID_SOCKET)return;
//	sockaddr_in sin;
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(8888);
//	sin.sin_addr.S_un.S_addr = INADDR_ANY;
//	if (::bind(SeverListen, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)return;
//	if (listen(SeverListen, 5) == SOCKET_ERROR)return;
//
//	SOCKET ClientSocket;
//	sockaddr_in RemoteAddr;
//	int RemoteAddrSize = sizeof(RemoteAddr);
//	char RevData[DataSize + 1];
//	FILE* fp = NULL;
//	errno_t err = 0;
//	/*err = fopen_s(&fp, "D:\\result.txt", "w");
//	if (err != 0) return;*/
//	SingleFileReceiver fr;
//	
//	connect(&fr, &SingleFileReceiver::finished, this, &FilesReceiver::SingleFileFinished);
//	while (ctnListen) {
//		ClientSocket = accept(SeverListen, (SOCKADDR*)&RemoteAddr, &RemoteAddrSize);
//		if (ClientSocket == INVALID_SOCKET)continue;
//
//		fr.socket = ClientSocket;
//		fr.start();
//
//		fr.wait();
//		/*fclose(fp);*/
//
//		closesocket(ClientSocket);
//	}
//	closesocket(SeverListen);
//	WSACleanup();
//
//	return;
}

void FilesReceiver::SingleFileFinished()
{
	emit SingleFileGot();
}

void FilesReceiver::ReceiveSingleFile(SOCKET socket)
{
	SingleFileReceiver* fr=new SingleFileReceiver;
	connect(fr, &SingleFileReceiver::finished, this, &FilesReceiver::SingleFileFinished);
	fr->socket = socket;
	fr->start();
}
