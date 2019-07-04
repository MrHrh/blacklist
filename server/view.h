/*************************************************************************
    > File Name: view.h
    > Created Time: Sat 15 Dec 2018 08:01:44 PM CST
 ************************************************************************/
#ifndef __VIEW_H
#define __VIEW_H
#include<iostream>
#include"Cmysql.h"
#include"public.h"
#include<json/json.h>
using namespace std;

class view
{
public:
	virtual void view_handle(int fd, Json::Value val) = 0;
private:
	Cmysql * _mysql;
};

class view_login:public view
{
public:
	view_login()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		string name = val["name"].asString();
		string pw = val["pw"].asString();
		bool res = _mysql->logintosql(name, pw);
		if(res)
			send(fd, "yes", 3, 0);
		else
			send(fd, "not", 3, 0);
	}
private:
	Cmysql * _mysql;
	
};

class view_register:public view
{
public:
	view_register()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		string name = val["name"].asString();
		string pw = val["pw"].asString();
		bool res = _mysql->registertosql(name, pw);
		if(res)
			send(fd, "yes", 3, 0);
		else
			send(fd, "not", 3, 0);
	}
private:
	Cmysql * _mysql;
};
class view_select:public view
{
public:
	view_select()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		string id = val["id"].asString();
		bool res = _mysql->selectfromsql(id);
		Json::Value val1;
		val1["type"] = SELECT;
		val1["fd"] = val["fd"];
		if(res)
		{
			val1["massage"] = "yes";
		}
		else
		{
			val1["massage"] = "not";
		}
		send(fd, val1.toStyledString().c_str(), val1.toStyledString().size(), 0);
	}
private:
	Cmysql * _mysql;
};
class view_insert:public view
{
public:
	view_insert()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		string id = val["id"].asString();
		string name = val["name"].asString();
		string sex = val["sex"].asString();
		int findtime = val["findtime"].asInt();
		int keeptime = val["keeptime"].asInt();
		bool res = _mysql->inserttosql(id, name, sex, findtime, keeptime);
		if(res)
			send(fd, "yes", 3, 0);
		else
			send(fd, "not", 3, 0);
	}
private:
	Cmysql * _mysql;
};
class view_update:public view
{
public:
	view_update()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		int choice = val["choice"].asInt();
		string id = val["id"].asString();
		string str = val["str"].asString();
		bool res = _mysql->updatefromsql(choice, id, str);
		if(res)
			send(fd, "yes", 3, 0);
		else
			send(fd, "not", 3, 0);
	}
private:
	Cmysql * _mysql;
};
class view_remove:public view
{
public:
	view_remove()
	{
		_mysql = new Cmysql();
	}
	void view_handle(int fd, Json::Value val)
	{
		string id = val["id"].asString();
		bool res = _mysql->deletefromsql(id);
		if(res)
			send(fd, "yes", 3, 0);
		else
			send(fd, "yes", 3, 0);
	}
private:
	Cmysql * _mysql;
};
#endif
