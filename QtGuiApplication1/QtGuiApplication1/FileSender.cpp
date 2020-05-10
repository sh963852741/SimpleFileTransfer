#include "FileSender.h"
#include "md5.h"
#include"compre.h"
#include <fstream>
using namespace std;

void FilesSender::BeginSending(QString basepath, QStringList filename,QString IPaddress)
{
	sthreadpool.setMaxThreadCount(4);
	for (int i = 0; i < filename.size(); i++)
	{
		SingleFileSender* fs = new SingleFileSender;
		fs->seqID = i;
		fs->iscompress = iscompress;
		fs->isencrypt = isencryption;
		fs->setAutoDelete(true);
		connect(fs, &SingleFileSender::begin, this, &FilesSender::process_begin);
		connect(fs, &SingleFileSender::complete, this, &FilesSender::process_complete);
		connect(fs, &SingleFileSender::compressing, this, &FilesSender::process_compress);
		connect(fs, &SingleFileSender::updatelog, this, &FilesSender::updatesendlog);
		fs->ipAddress = IPaddress.mid(0, IPaddress.indexOf(":")).toLocal8Bit();
		fs->port = IPaddress.mid(IPaddress.indexOf(":")+1).toLocal8Bit();
		fs->floderName = basepath.toLocal8Bit();
		fs->fileName = filename[i].toLocal8Bit();
		sthreadpool.start(fs);
	}
}

void SingleFileSender::run()
{
	//emit begin(seqID);
	const int RecDataSize = 255;
	WORD SockVersion = MAKEWORD(2, 2);
	WSADATA WsaData;
	int CheckWSA = WSAStartup(SockVersion, &WsaData);
	if (CheckWSA != 0)return;
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)return;
	sockaddr_in ClientAddr;
	ClientAddr.sin_family = AF_INET;
	//ClientAddr.sin_port = htons(8888);
	ClientAddr.sin_port = htons(atoi(port.c_str()));
	const char* IPdotdec = ipAddress.c_str();
	//char IPdotdec[] = "127.0.0.1";
	inet_pton(AF_INET, IPdotdec, &ClientAddr.sin_addr.S_un);
	if (::connect(ClientSocket, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr)) == SOCKET_ERROR)
	{
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}
	string tempfile;
	ifstream fp;
	if (iscompress)
	{
		string fullname = floderName + fileName;
		tempfile = fullname;
		tempfile.append(".tmp");
		//tempfile.replace(tempfile.begin() + tempfile.find_last_of('.'), tempfile.end(), ".tmp");
		emit compressing(seqID);
		def(fullname, tempfile, Z_DEFAULT_COMPRESSION);
		fp.open(tempfile, ios::binary);
	}
	else
		fp.open(floderName + fileName, ios::binary);
	emit begin(seqID);
	fp.seekg(0, ios::end);
	unsigned long long int fileSize = fp.tellg();

	int CheckSend;
	unsigned char buffer[1024];

	unsigned int x = 3;
	unsigned long long int beginPosition = 0;

	if (iscompress&&!isencrypt)   x = 4;//压缩
	if (!iscompress && isencrypt) x = 5;//加密
	if (iscompress&&isencrypt)    x = 6;//压缩和加密

	memset(buffer, 0, 1024);
	memcpy_s(&buffer[0], 4, &x, 4);
	memcpy_s(&buffer[4], 8, &fileSize, 8);
	memcpy_s(&buffer[12], 8, &beginPosition, 8);
	memcpy_s(&buffer[20], 1004, fileName.c_str(), fileName.length());

	if (isencrypt)
	{
		for (int i = 0; i < 1024; i++)
		{
			buffer[i] -= 4;
		}
	}
	const char* SendLength = (char*)buffer;
	CheckSend = send(ClientSocket, SendLength, 1024, 0);

	int l = recv(ClientSocket, (char*)&beginPosition, 8, 0);
	fp.seekg(beginPosition, ios::beg);

	for (unsigned long long int i = beginPosition; i < fileSize; i += CheckSend)
	{
		fp.read((char*)buffer, 1024);

		if (isencrypt)
		{
			for (int i = 0; i < 1024; i++)
			{
				buffer[i] -= 4;
			}
		}
		const unsigned char* SendData = buffer;
		CheckSend = send(ClientSocket, (char*)SendData, fp.gcount(), 0);

		if (CheckSend == SOCKET_ERROR || CheckSend == 0)
		{
			closesocket(ClientSocket);
			WSACleanup();
			emit complete(seqID, false, "发送失败");
			return;
		}
	}
	fp.seekg(0, ios::beg);
	CheckSend = recv(ClientSocket, (char*)buffer, 33, 0);
	if (CheckSend == SOCKET_ERROR || CheckSend == 0)
	{
		emit updatelog(QString::fromLocal8Bit(floderName.c_str()),QString::fromLocal8Bit( fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("发送失败"));
		emit complete(seqID, false, "发送失败");
	}
	else
	{
		MD5 md5;
		md5.update(ifstream(floderName + fileName, ios::binary));
		string res = md5.toString();
		if (strcmp(res.c_str(), (char*)buffer) != 0)
		{
			char msg[] = "md5 check error";
			send(ClientSocket, msg, 16, 0);
			emit updatelog(QString::fromLocal8Bit(floderName.c_str()), QString::fromLocal8Bit(fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("发送失败"));
			emit complete(seqID, false, "发送失败");
			return;
		}
		else
		{
			char msg[] = "finish";
			send(ClientSocket, msg, 16, 0);
		}
	}
	closesocket(ClientSocket);
	WSACleanup();
	if (iscompress)
	{
		QString str = QString::fromLocal8Bit(tempfile.c_str());
		QFile::remove(str);
	}
	emit updatelog(QString::fromLocal8Bit(floderName.c_str()), QString::fromLocal8Bit(fileName.c_str()), QTime::currentTime(), QString::fromLocal8Bit("发送成功"));
	emit complete(seqID, true, "");
	return;
}

void FilesSender::updatesendlog(QString basepath, QString filename, QTime time, QString mes)
{
	ofstream output;
	output.open("sendlog.csv", ios::app);
	string nowtime = time.toString("h:m:s").toLocal8Bit();
	string floder = basepath.toLocal8Bit();
	string file = filename.toLocal8Bit();
	string message = mes.toLocal8Bit();
	output << nowtime<<","<<floder<<","<<file<<","<<message<<'\n';
	output.close();
}
void FilesSender::StopSending()
{

}

void FilesSender::setcompress(bool a)
{
	iscompress = a;
}

void FilesSender::setencrypt(bool a)
{
	isencryption = a;
	
}

void FilesSender::process_compress(unsigned short id)
{
	emit rpt_process(id, QString::fromLocal8Bit("正在压缩"));
}

void FilesSender::process_begin(unsigned short id)
{
	emit rpt_process(id, QString::fromLocal8Bit("开始传输"));
}
void FilesSender::process_process(unsigned short id, int value)
{
	emit rpt_process(id, QString::fromLocal8Bit("正在传输"));
}
void FilesSender::process_complete(unsigned short id, bool success, QString msg)
{
	emit rpt_process(id, QString::fromLocal8Bit(success ? "传输完成" : "传输失败"));
}