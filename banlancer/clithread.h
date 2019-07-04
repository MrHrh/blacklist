/*************************************************************************
    > File Name: clithread.h
    > Created Time: Tue 15 Jan 2019 06:03:39 PM CST
 ************************************************************************/
#ifndef __CLITHREAD_H
#define __CLITHREAD_H
#include<iostream>
#include"Node.h"
#include"mdfive.h"
#include<map>
#include<string>
using namespace std;

class clithread
{
private:
	map<int, Node*>*_nodemap;
	CtcpServer* _client_server;
public:
	clithread(CtcpServer* client_server, map<int, Node*>*nodemap)
	{
		_nodemap = nodemap;
		_client_server = client_server;
		pthread_t pid;
		pthread_create(&pid, NULL, clithread::run, this);
	}
	static void *run(void *arg)
	{
		clithread * This = static_cast<clithread*>(arg);
		while(1)
		{
			int clifd = This->_client_server->Accept();
			cout<<"one client is try to get a link..."<<endl;

			if(clifd <= 0)
			{
				cout<<"client break"<<endl;
				return NULL;
			}
		
			struct sockaddr_in peeraddr;
			socklen_t len = sizeof(peeraddr);
			if(-1 == getpeername(clifd, (struct sockaddr*)&peeraddr, &len))
			{
				cout<<"get clifd fail"<<endl;
				return NULL;
			}
		

			string ip = inet_ntoa(peeraddr.sin_addr);
			int port = ntohs(peeraddr.sin_port);

			mdfive tmd(ip, port);
			tmd.usemd();
			long hash = tmd.getmdnum();
			long index = hashlist::gethashlist()->findvnode(hash);

			string server_ip;
			int server_port;
			map<int, Node*>::iterator it = This->_nodemap->begin();
			for(; it!=This->_nodemap->end(); it++)
			{
				if(it->second->isindex(index))
				{
					it->second->getaddress(server_ip, server_port);
				}
			}
		
			Json::Value val;
			val["ip"] = server_ip.c_str();
			val["port"] = server_port;
			string message = val.toStyledString();
			int mlen = message.size();
			send(clifd, message.c_str(), mlen, 0);
		}
		return NULL;
	}
};

#endif
