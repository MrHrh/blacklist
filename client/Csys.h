/*************************************************************************
    > File Name: Csys.h
    > Created Time: Sun 25 Nov 2018 04:16:15 PM CST
 ************************************************************************/
#ifndef __CSYS_H
#define __CSYS_H
#include"Cworker.h"
#include"public.h"
#include<json/json.h>
#include<iostream>
using namespace std;

class Csys
{
public:
	Csys();
	void put();//登录注册的菜单
	void Login();
	void Register();
private:
	Cworker* _worker;
};

Csys::Csys()
{
	_worker = new Cworker();
}
void Csys::put()//登录注册菜单
{
	while(1)
	{
		cout<<"1.login"<<endl;
		cout<<"2.register"<<endl;
		cout<<"3.exit"<<endl;
		cout<<"please input:";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 1:
				Login();
				break;
			case 2:
				Register();
				break;
			case 3:
				cout<<"thanks for your use!"<<endl;
				return;
			default:
				cout<<"input wrong! please input again"<<endl;
		}
	}
}
void Csys::Login()
{
	string name;
	string password;
	cout<<"name:";
	cin>>name;
	cout<<"password:";
	cin>>password;

	Json::Value val;
	val["type"] = LOGIN;
	val["name"] = name.c_str();
	val["pw"] = password.c_str();
	CworkSer::getWorkSer()->Send(val.toStyledString());//发送给服务器进行验证
	string RecvBuff;
	CworkSer::getWorkSer()->Recv(RecvBuff);//接收服务器的返回
	cout<<"recv: "<<RecvBuff<<endl;
	if(strcmp(RecvBuff.c_str(), "yes") == 0)
	{
		cout<<"login successful"<<endl;
		_worker->run();
		_worker->~Cworker();
	}
	else
	{
		cout<<"login error"<<endl;
	}
}

void Csys::Register()
{
	string name;
	string password;
	string surepass;
	cout<<"name:";
	cin>>name;
	cout<<"password:";
	cin>>password;
	cout<<"identify your password:";
	cin>>surepass;
	while(password != surepass)
	{
		cout<<"different password!"<<endl;
		cout<<"password:";
		cin>>password;
		cout<<"identify your password:";
		cin>>surepass;
	}

	Json::Value val;
	val["type"] = REGISTER;
	val["name"] = name.c_str();
	val["pw"] = password.c_str();

	CworkSer::getWorkSer()->Send(val.toStyledString());
	string RecvBuff;
	CworkSer::getWorkSer()->Recv(RecvBuff);
	if(strcmp(RecvBuff.c_str(),"yes") == 0)
	{
		cout<<"register successful!"<<endl;
	}
}

#endif
