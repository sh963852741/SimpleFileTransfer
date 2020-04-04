#include "FileSender.h"

void FilesSender::BeginSending()
{
	SingleFileSender fs,fs1;
	fs.start();
	//fs1.start();
	fs.wait();
	//fs1.wait();
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
		char IPdotdec[] = "127.0.0.1";
		inet_pton(AF_INET, IPdotdec, &ClientAddr.sin_addr.S_un);
		if (::connect(ClientSocket, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr)) == SOCKET_ERROR) 
		{
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}
		char fileName[] = "D:\\src.txt";
		FILE* fp = NULL;
		errno_t err = 0;
		while (true) {
			err = fopen_s(&fp, fileName, "rb");
			if (err == 0) break;
		}
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		int CheckSend;
		const int groupLength = 255;
		unsigned char buffer[groupLength];
		int count = fileSize / groupLength + 1;
		sprintf_s((char*)buffer, 20, "%d", count);
		const char* SendLength = (char*)buffer;

		CheckSend = send(ClientSocket, SendLength, strlen(SendLength), 0);
		fseek(fp, 0, SEEK_SET);
		for (int i = 0; i < count; i++)
		{
			int tempLength = fread_s(buffer,255, sizeof(unsigned char), groupLength, fp);
			const unsigned char* SendData = buffer;
			CheckSend = send(ClientSocket, (char*)SendData, strlen((char*)SendData), 0);


			if (CheckSend == SOCKET_ERROR) {
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
		}
		closesocket(ClientSocket);
		fclose(fp);
	WSACleanup();
	return ;
}