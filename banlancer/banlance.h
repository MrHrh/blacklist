/*************************************************************************
    > File Name: banlance.h
    > Created Time: Wed 09 Jan 2019 06:55:47 PM CST
 ************************************************************************/
#ifndef __BANLANCE_H
#define __BANLANCE_H

#include<iostream>
#include<map>
#include<event.h>
#include<json/json.h>
#include"Node.h"
#include"mdfive.h"
#include"CtcpServer.h"
#include"threadpool.h"
using namespace std;

class banlance
{
private:
	Node *_node;
	int _count;
	static map<int, event*>_eventmap;
	map<int, Node*>_nodemap;
	CtcpServer *_client_server;
	CtcpServer *_server_server;
	static event_base * _base;
	threadpool *_pool;
public:
	banlance(int _client_port, int _server_port)
	{
		_client_server = new CtcpServer(_client_port, "127.0.0.1");
		_server_server = new CtcpServer(_server_port, "127.0.0.1");
		
		_pool = new threadpool(_client_server, &_nodemap);

		_base = event_base_new();
		struct event *serverEvent = event_new(_base, _server_server->Get_sockfd(), EV_READ|EV_PERSIST, banlance::servercb, this);

		if(serverEvent == NULL)
		{
			cout<<"serverEvent create fail"<<endl;
			return;
		}
		
		event_add(serverEvent, NULL);
	}
	//程序入口
	void run()
	{
		cout<<"load banlance is running..."<<endl;
		event_base_dispatch(_base);
	}
	//服务器链接接受回调函数
	static void servercb(int fd, short event, void *arg)
	{
		cout<<"add a new server"<<endl;
		banlance *This = static_cast<banlance*>(arg);

		int serfd = This->_server_server->Accept();
		if(serfd == -1)
		{
			cout<<"server link fail"<<endl;
			return;
		}
		
		struct event *serEvent = event_new(_base, serfd, EV_READ|EV_PERSIST, banlance::servercall, This);
		if(serEvent == NULL)
		{
			cout<<"server event new fail"<<endl;
		}
		event_add(serEvent, NULL);
		_eventmap.insert(make_pair(serfd, serEvent));
		cout<<"add successful"<<endl;
	}
	//与唯一一个服务器进行通讯的回调函数
	static void servercall(int fd, short event, void *arg)
	{
		banlance *This = static_cast<banlance*>(arg);
		char buff[128] = {0};
		int res = recv(fd, buff, 127, 0);
		//服务器宕机时
		if(res <= 0)
		{
			event_free(_eventmap[fd]);
			_eventmap.erase(fd);
			This->_nodemap[fd]->~Node();
			This->_nodemap.erase(fd);
			cout<<"one server is broke, please check"<<endl;
			return;
		}

		Json::Value val;
		Json::Reader read;
		if(!read.parse(buff, val))
		{
			cout<<"read recvbuff fail"<<endl;
			return;
		}

		string ip = val["ip"].asString();
		int port = val["port"].asInt();
		int count = val["count"].asInt();

		This->_node = new Node(ip, port, count);
		This->_node->createvnode();
		This->_nodemap.insert(make_pair(fd, This->_node));
		This->_count++;
	}
};

event_base*banlance::_base = NULL;
map<int, event*>banlance::_eventmap;
#endif
