#include "FileSender.h"
#include <fstream>
using namespace std;

void FilesSender::BeginSending()
{
	SingleFileSender fs, fs1;
	fs.floderName = R"(D:\系统镜像\)";
	fs.fileName = "cn_visual_studio_2010_ultimate_x86_dvd_532347.iso";
	fs1.floderName = R"(D:\系统镜像\)";
	fs1.fileName = "mclauncher_1.5.0.5724.exe";
	fs.start();
	fs1.start();
	fs.wait();
	fs1.wait();
	fs.quit();
	fs1.quit();
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
	fp.open(floderName + fileName, ios::binary);
	fp.seekg(0, ios::end);
	unsigned int fileSize = fp.tellg();


	int CheckSend;
	unsigned char buffer[1024];

	/*告知服务器开始上传文件*/
	unsigned int x = 3, beginPosition = 0;
	memset(buffer, 0, 1024);
	memcpy_s(&buffer[0], 4, &x, 4);
	memcpy_s(&buffer[4], 4, &fileSize, 4);
	memcpy_s(&buffer[8], 4, &beginPosition, 4);
	memcpy_s(&buffer[12], 1012, fileName.c_str(), fileName.length());
	const char* SendLength = (char*)buffer;
	CheckSend = send(ClientSocket, SendLength, 1024, 0);

	/*移动文件指针*/
	int l = recv(ClientSocket, (char*)&beginPosition, 4, 0);
	fp.seekg(beginPosition, ios::beg);

	for (unsigned int i = beginPosition; i < fileSize; i += CheckSend)
	{
		fp.read((char*)buffer, 1024);
		const unsigned char* SendData = buffer;
		CheckSend = send(ClientSocket, (char*)SendData, fp.gcount(), 0);

		if (CheckSend == SOCKET_ERROR || isInterruptionRequested())
		{
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}
	}
	fp.close();
	if (recv(ClientSocket, (char*)buffer, 7, 0) == SOCKET_ERROR)
	{

	}
	closesocket(ClientSocket);
	WSACleanup();
	return;
}

void FilesSender::StopSending()
{
}
