/*************************************************************************
    > File Name: Csys.h
    > Created Time: Fri 07 Dec 2018 02:43:55 PM CST
 ************************************************************************/

#ifndef __CSYS_H
#define __CSYS_H
#include<iostream>
#include"CtcpServer.h"
#include"CtcpConnect.h"
#include"CthreadPool.h"
using namespace std;

class Csys
{
public:
	/*监听套接字的回调函数*/
	static void listenCb(int fd, short event, void* arg)
	{
		CtcpServer* server = static_cast<CtcpServer*>(arg);
		int cliFd = server->Accept();
		printf("%d is linking\n", cliFd);
		if(-1 == cliFd)
		{
			cout<<"server accept error"<<endl;
			return;
		}

		CthreadPool::GetThreadPool()->SendToWorkThread(cliFd);
		
	}
	
	void run()
	{
		event_base_dispatch(_base);
	}
	Csys()
	{
		int load, server;
		cout<<"please input the server's port:"<<endl;
		cin>>server;
		_server = new CtcpServer(server, "127.0.0.1");
		if(NULL == _server)
		{
			cout<<"connot get the server"<<endl;
			return;
		}
		
		cout<<"please input the load banlance's port:"<<endl;
		cin>>load;
		Json::Value val;
		val["ip"] = "127.0.0.1";
		val["port"] = server;
		val["count"] = 20;
		_Connect = new CtcpConnect(load, "127.0.0.1");
		if(_Connect->Send(val.toStyledString()) == -1)
		{
			cout<<"send to load banlance fail"<<endl;
			return;
		}
		_Connect->Send(val.toStyledString());

		CthreadPool::GetThreadPool();

		_base = event_base_new();
		struct event *listenEvent = event_new(_base, _server->Get_sockfd(), EV_READ|EV_PERSIST, Csys::listenCb, _server);
		if(NULL == listenEvent)
		{
			cout<<"ser listen event create fail"<<endl;
			return;
		}
		event_add(listenEvent, NULL);
	}
private:
	CtcpServer* _server;
	CtcpConnect* _Connect;
	static event_base* _base;
};

event_base*Csys::_base = NULL;

#endif
