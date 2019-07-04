/*************************************************************************
    > File Name: CworkSer.h
    > Created Time: Mon 26 Nov 2018 06:51:02 PM CST
 ************************************************************************/

#ifndef __CWORKSER_H
#define __CWORKSER_H

#include"CtcpConnect.h"
#include"public.h"
#include<iostream>
#include<json/json.h>
#include<pthread.h>
using namespace std;
pthread_mutex_t m;

class CworkSer
{
public:
	static CworkSer* getWorkSer()
	{
		if(_workser == NULL)
		{
			pthread_mutex_lock(&m);
			if(_workser == NULL)
			{
				_workser = new CworkSer();
			}
			pthread_mutex_unlock(&m);
		}
		return _workser;
	}

	int Send(string SendBuff)
	{
		return _tcpconnect->Send(SendBuff);
	}
	int Recv(string &RecvBuff)
	{
		return _tcpconnect->Recv(RecvBuff);
	}	
private:
	CworkSer()//单例模式，构造函数实现成私有的
	{
		cout<<"please input the load banlance's port:"<<endl;
		cin>>_banlanceport;
		_banlanceip = "127.0.0.1";
		_tcpconnect = new CtcpConnect(_banlanceport, _banlanceip);
		string str;
		_tcpconnect->Recv(str);

		Json::Value val;
		Json::Reader read;

		if(-1 == read.parse(str.c_str(), val))
		{
			cout<<"read load banlance json fail"<<endl;
			return;
		}
		
		string ipnew = val["ip"].asString();
		short portnew = val["port"].asInt();

		_tcpconnect->Close();
		delete _tcpconnect;
		_tcpconnect = new CtcpConnect(portnew, ipnew);//构造tcpconnect封装类的对象
	}
	string _banlanceip;
	short _banlanceport;
	static CworkSer* _workser;//WorkSer类的单例对象
	CtcpConnect* _tcpconnect;//tcpconnect类对象指针
};
CworkSer* CworkSer::_workser = NULL;

#endif
