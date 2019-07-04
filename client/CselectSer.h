/*************************************************************************
    > File Name: CselectSer.h
    > Created Time: Mon 26 Nov 2018 08:26:51 PM CST
 ************************************************************************/

#ifndef CSELECTSER_H
#define CSELECTSER_H

#include<map>
#include<json/json.h>
#include<event.h>
#include"public.h"
#include"CtcpServer.h"
#include"CworkSer.h"
#include<iostream>
using namespace std;

class CselectSer
{
public:
	int Send(int fd, string SendBuff)
	{
		return _selectser->Send(fd, SendBuff);
	}
	int Recv(int fd, string RecvBuff)
	{
		return _selectser->Recv(fd, RecvBuff);
	}
	static void listenCb(int fd, short event, void* arg)
	{
		CtcpServer *server = static_cast<CtcpServer*>(arg);
		int cliFd = server->Accept();
		if(-1 == cliFd)
		{
			cout<<"selecter cli accept fail;Errno:"<<endl;
			event_free(_eventMap[cliFd]);
			_eventMap.erase(cliFd);
			return;
		}

		struct event*cliEvent = event_new(_base, cliFd, EV_READ|EV_PERSIST, CselectSer::cliCb, server);
		if(NULL == cliEvent)
		{
			cout<<"select ser thread cli event new fail;errno:"<<endl;
			return;
		}
		_eventMap.insert(make_pair(cliFd, cliEvent));
		event_add(cliEvent, NULL);
	}
	static void cliCb(int fd, short event, void* arg)
	{
		CtcpServer* server = static_cast<CtcpServer*>(arg);

		string id;//用来接收要查询用户的id
		if(0 >= server->Recv(fd, id))
		{
			cout<<endl<<"select cli shot down!"<<endl;
			event_free(_eventMap[fd]);
			_eventMap.erase(fd);
			close(fd);
			return;
		}
		
		Json::Value val;
		val["type"] = SELECT;
		val["fd"] = fd;
		val["massage"] = id.c_str();

		CworkSer::getWorkSer()->Send(val.toStyledString());
	}

	static void *selectThreadRun(void *arg)
	{
		event_base_dispatch(_base);
	}

	CselectSer()
	{
		int port;
		cout<<"please input the selectser's port: ";
		cin>>port;
		_selectser = new CtcpServer(port, "127.0.0.1");
		_base = event_base_new();

		struct event *listenEvent = event_new(_base, _selectser->Get_sockfd(), EV_READ|EV_PERSIST, CselectSer::listenCb, _selectser);

		if(NULL == listenEvent)
		{
			cout<<"select ser listen event create fail;errno:"<<endl;
			return;
		}
		event_add(listenEvent, NULL);

		pthread_t pid;
		//创建线程循环监听
		pthread_create(&pid,NULL, CselectSer::selectThreadRun, _base);
	}
	//发送信息给信息采集机
	void sendSelect(int fd, string str)
	{
		_selectser->Send(fd,str);
	}
private:
	CtcpServer* _selectser;
	static event_base* _base;
	static map<int,struct event*>_eventMap;
};
event_base*CselectSer::_base = NULL;
map<int,struct event*> CselectSer::_eventMap;

#endif
