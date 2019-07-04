/*************************************************************************
    > File Name: threadpool.h
    > Created Time: Tue 15 Jan 2019 05:57:20 PM CST
 ************************************************************************/
#ifndef __THREADPOOL_H
#define __THREADPOOL_H
#include<iostream>
#include"clithread.h"
#include"banlance.h"
#include"CtcpServer.h"
using namespace std;

class threadpool
{
private:
	clithread *_thread[3];
public:
	threadpool(CtcpServer *client_server, map<int, Node*>*nodemap)
	{
		int i = 0;
		for(; i < 3; i++)
		{
			_thread[i] = new clithread(client_server, nodemap);
		}
	}
};

#endif
