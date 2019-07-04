/*************************************************************************
    > File Name: Cworker.h
    > Created Time: Mon 26 Nov 2018 08:30:42 PM CST
 ************************************************************************/

#ifndef __CWORKER_H
#define __CWORKER_H

#include<stdlib.h>
#include"public.h"
#include"CworkSer.h"
#include"CselectSer.h"
#include<iostream>
#include<pthread.h>
#include<json/json.h>
using namespace std;

class Cworker
{
public:
	Cworker()
	{
		_selectser = new CselectSer();
	}
	~Cworker()
	{
		delete _selectser;
		pthread_cancel(_pthid);
	}
	static void *recvFromWorkSer(void *arg)//监听函数
	{
		CselectSer* selectser = static_cast<CselectSer*>(arg);
		while(1)
		{
			string RecvBuff;
			int err = CworkSer::getWorkSer()->Recv(RecvBuff);
			if(err <= 0)
			{
				cout<<endl<<"server is break"<<endl;
				exit(0);
			}
			Json::Value val;
			Json::Reader read;
			if(!read.parse(RecvBuff.c_str(),val))
			{
				cout<<"read RecvBuff error"<<RecvBuff<<endl;
				continue;
			}

			if(val["type"].asInt() == SELECT && val["fd"].asInt() != -1)
			{
				int fd = val["fd"].asInt();
				string str = val["massage"].asString();
				selectser->Send(fd, str);
			}
			else
			{
				cout<<val["massage"].asString()<<endl;
			}
		}
	}

	void run()
	{
		//监听服务器传回来的数据
		pthread_create(&_pthid, NULL, Cworker::recvFromWorkSer, _selectser);
		int choice = 0;
		while(1)
		{
			menu();
			cout<<"input your choice:";
			cin>>choice;
			switch(choice)
			{
				case 1:
					{
						Select();
						break;
					}
				case 2:
					{
						Insert();
						break;
					}
				case 3:
					{
						Delete();
						break;
					}
				case 4:
					{
						Update();
						break;
					}
				case 5:
					cout<<"thanks for your use"<<endl;
					return;
				default:
					{
						cout<<"error choice"<<endl;
						break;
					}
			}
		}
	}

	void menu()
	{
		cout<<"1.select"<<endl;
		cout<<"2.insert"<<endl;
		cout<<"3.delete"<<endl;
		cout<<"4.update"<<endl;
		cout<<"5.exit"<<endl;
	}

	/*功能函数*/
	void Select()
	{
		string id;
		cout<<"input id:";
		cin>>id;

		Json::Value val;
		val["type"] = SELECT;
		val["fd"] = -1;
		val["id"] = id.c_str();

		CworkSer::getWorkSer()->Send(val.toStyledString());
	}
	void Insert()
	{
		string name;
		cout<<"input name:";
		cin>>name;

		string id;
		cout<<"input id:";
		cin>>id;

		string sex;
		cout<<"input sex:";
		cin>>sex;

		int findtime;
		cout<<"input findtime:";
		cin>>findtime;
	
		int keeptime;
		cout<<"input keeptime:";
		cin>>keeptime;

		Json::Value val;
		val["type"] = INSERT;
		val["name"] = name.c_str();
		val["id"] = id.c_str();
		val["sex"] = sex.c_str();
		val["findtime"] = findtime;
		val["keeptime"] = keeptime;

		CworkSer::getWorkSer()->Send(val.toStyledString());

	}
	void Update()
	{
		cout<<"this function isn't developed!"<<endl;
	}
	void Delete()
	{
		cout<<"this function isn't developed!"<<endl;
	}

private:
	CselectSer* _selectser;
	pthread_t _pthid;
};

#endif
