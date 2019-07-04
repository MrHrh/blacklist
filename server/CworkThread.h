/*************************************************************************
    > File Name: CworkThread.h
    > Created Time: Fri 07 Dec 2018 05:39:04 PM CST
 ************************************************************************/
#ifndef __CWORKTHREAD_H
#define __CWORKTHREAD_H
#include<iostream>
#include<pthread.h>
#include<event.h>
#include"Contral.h"
#include<map>
using namespace std;


class CworkThread
{
public:
	int Return_link_num()
	{
		return _linkcount;
	}
	void GetLink(int fd)
	{
		cout<<"GetLink..."<<endl;
		struct event* cliEvent = event_new(_workbase, fd, EV_READ|EV_PERSIST, cliCb, this);
		

		if(NULL == cliEvent)
		{
			cout<<"workthread event new fail"<<endl;
			return;
		}
		_eventMap.insert(make_pair(fd, cliEvent));
		event_add(cliEvent, NULL);
		_linkcount++;
		cout<<"GetLink OK"<<endl;
	}
	static void cliCb(int fd, short event, void *arg)
	{
		cout<<"cliCb..."<<endl;
		CworkThread* This = static_cast<CworkThread*>(arg);
		char buff[128] = {0};
		if(0 >= recv(fd, buff, 127, 0))
		{
			close(fd);
			event_free(This->_eventMap[fd]);
			This->_eventMap.erase(fd);
			This->_linkcount--;
			cout<<fd<<" cli break link"<<endl;
			return;
		}
		Json::Value val;
		Json::Reader read;
		if(-1 == read.parse(buff, val))
		{
			cout<<"read json fail"<<endl;
			return;
		}
		cout<<"data has send to database"<<endl;
		cout<<"fd cliCb OK"<<endl;
		This->_contral->process(fd, val);
	}
	static void *WorkThreadRun(void *arg)
	{
		CworkThread* This = static_cast<CworkThread*>(arg);
		while(1)
		{
			event_base_dispatch(This->_workbase);
		}
	}
	CworkThread()
	{
		pthread_t tid;
		_linkcount = 0;
		_contral = new contral();
		_workbase = event_base_new();
		int ret = pthread_create(&tid, NULL, WorkThreadRun, this);
		cout<<tid<<" is running"<<endl;
	}	
private:
	int _linkcount;
	event_base* _workbase;
 	map<int, struct event*>_eventMap;
	contral *_contral;
};

#endif
