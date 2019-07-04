/*************************************************************************
    > File Name: CthreadPool.h
    > Created Time: Fri 07 Dec 2018 03:14:46 PM CST
 ************************************************************************/
#ifndef __CTHREADPOOL_H
#define __CTHREADPOOL_H
#include<iostream>
#include"CworkThread.h"
#include<pthread.h>
using namespace std;

pthread_mutex_t m;

class CthreadPool
{
public:
	static int GetWorkThre_link(CworkThread *workthread)
	{
		return workthread->Return_link_num();
	}
	void SendToWorkThread(int fd)
	{
		int num1 = GetWorkThre_link(_workthread[0]);
		cout<<"num1: "<<num1<<endl;
		int num2 = GetWorkThre_link(_workthread[1]);
		cout<<"num2: "<<num2<<endl;
		int num3 = GetWorkThre_link(_workthread[2]);
		cout<<"num3: "<<num3<<endl;

		if(num1 <= num2)
		{
			if(num1 <= num3)
			{
				cout<<"first workthread has a new link"<<endl;
				_workthread[0]->GetLink(fd);
			}
			else
			{
				cout<<"thrid workthread has a new link"<<endl;
				_workthread[2]->GetLink(fd);
			}
		}
		else
		{
			if(num2 <= num3)
			{
				cout<<"second workthread has a new link"<<endl;
				_workthread[1]->GetLink(fd);
			}
			else
			{
				cout<<"third workthread has a new link"<<endl;
				_workthread[2]->GetLink(fd);
			}
		}
	}
	static CthreadPool* GetThreadPool()
	{
		if(_threadpool == NULL)
		{
			pthread_mutex_lock(&m);
			if(_threadpool == NULL)
			{
				_threadpool = new CthreadPool();
			}
			pthread_mutex_unlock(&m);
		}
		return _threadpool;
	}
private:
	CthreadPool()
	{
		int i = 0;
		pthread_t tid[3];
		for(; i < 3; i++)
		{
			_workthread[i] = new CworkThread();
		}
	}
	static CthreadPool *_threadpool;
	static CworkThread *_workthread[3];
};

CthreadPool*CthreadPool::_threadpool = NULL;
CworkThread *CthreadPool::_workthread[3] = {0};

#endif
