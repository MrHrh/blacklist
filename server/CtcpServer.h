/*************************************************************************
    > File Name: tcpServer.h
    > Created Time: Sun 25 Nov 2018 09:55:44 AM CST
 ************************************************************************/
#ifndef __CTCPSERVER_H
#define	__CTCPSERVER_H

#include<iostream>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

class CtcpServer
{
public:
	CtcpServer(short port, string ip);
	int Bind();
	int Listen();
	int Accept();
	ssize_t Recv(int fd,string RecvBuff);
	ssize_t Send(int fd,string SendBuff);
	int Close();
	int Get_sockfd();
private:
	short _port;
	string _ip;
	int _sockfd;
};

CtcpServer::CtcpServer(short port, string ip)
{
	_port = port;
	_ip = ip;
	_sockfd = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(_port);
	ser.sin_addr.s_addr = inet_addr(_ip.c_str());
	int err = bind(_sockfd, (struct sockaddr*)&ser, sizeof(ser));
	if(err == -1)
	{
		cout<<"bind error"<<endl;
		return;
	}
	err = listen(_sockfd, 5);
	if(err == -1)
	{
		cout<<"listen error"<<endl;
		return;
	}

}

int CtcpServer::Accept()
{
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);
	return accept(_sockfd, (struct sockaddr*)&cli, &len);
}
ssize_t CtcpServer::Recv(int fd,string RecvBuff)
{
	char buff[100] = {0};
	int err = recv(fd, buff, 100, 0);
	RecvBuff = buff;
	return err;
}
ssize_t CtcpServer::Send(int fd, string SendBuff)
{
	socklen_t len = SendBuff.size();
	return send(fd, SendBuff.c_str(), len, 0);
}
int CtcpServer::Close()
{
	return close(_sockfd);
}
int CtcpServer::Get_sockfd()
{
	return _sockfd;
}

#endif
