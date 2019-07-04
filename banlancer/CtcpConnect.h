/*************************************************************************
    > File Name: CtcpConnect.h
    > Created Time: Sun 25 Nov 2018 01:39:23 PM CST
 ************************************************************************/
#ifndef	__CTCPCONNECT_H
#define __CTCPCONNECT_H
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<iostream>
#include<string>
using namespace std;


class CtcpConnect
{
public:
	CtcpConnect(short port, string ip);
	int Connect();
	int Send(string SendBuff);
	int Recv(string &RecvBuff);
	int Close();
	int Get_sockfd();
private:
	short _port;
	string _ip;
	int _sockfd;
};

CtcpConnect::CtcpConnect(short port, string ip)
{
	_ip = ip;
	_port = port;
	_sockfd = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(_port);
	ser.sin_addr.s_addr = inet_addr(_ip.c_str());

	int res = connect(_sockfd,(struct sockaddr*)&ser, sizeof(ser));
	if(res == -1)
	{
		cout<<"cannot get the srever"<<endl;
	}
}


int CtcpConnect::Send(string SendBuff)
{
	int len = SendBuff.size();
	return send(_sockfd, SendBuff.c_str(), len, 0);
}
int CtcpConnect::Recv(string &RecvBuff)
{
	char buff[100] = {0};
	int err = recv(_sockfd, buff, 100, 0);
	RecvBuff = buff;
	return err;
}
int CtcpConnect::Close()
{
	return close(_sockfd);
}

int CtcpConnect::Get_sockfd()
{
	return _sockfd;
}

#endif
