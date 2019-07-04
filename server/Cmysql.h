/*************************************************************************
    > File Name: Cmysql.h
    > Created Time: Sun 06 Jan 2019 11:17:12 AM CST
 ************************************************************************/
#ifndef __CMYSQL_H
#define __CMYSQL_H

#include<iostream>
#include<mysql/mysql.h>
using namespace std;

class Cmysql
{
private:
	MYSQL* _mpcon;
	MYSQL_RES * _mp_res;
	MYSQL_ROW _mp_row;
public:
	Cmysql();
	bool registertosql(string name, string password);
	bool logintosql(string name, string password);
	bool inserttosql(string id, string name, string sex, int findtime, int keeptime);
	bool deletefromsql(string id);
	bool updatefromsql(int choice, string id, string str);
	bool selectfromsql(string id);
};

Cmysql::Cmysql()
{
	_mpcon = mysql_init((MYSQL*)0);
	if(!mysql_real_connect(_mpcon,"127.0.0.1","root","111111",NULL,3306,NULL,0))
	{
		cout<<"mysql cannot connect"<<endl;
		return ;
	}
	if(mysql_select_db(_mpcon, "blacklist"))
	{
		cout<<"connot connect to the database "<<endl;
		return ;
	}
}

bool Cmysql::registertosql(string name, string password)
{
	char cmd[100] = {"insert into manager values('"};
	sprintf(cmd + strlen(cmd), "%s','%s');", name.c_str(), password.c_str());

	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		return false;
	}
	
	return true;
}
bool Cmysql::logintosql(string name, string password)
{
	char cmd[100] = {"select * from manager where name='"};
	sprintf(cmd + strlen(cmd), "%s';", name.c_str());
	
	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		return false;
	}
	_mp_res = mysql_store_result(_mpcon);
	_mp_row = mysql_fetch_row(_mp_res);
	if(_mp_row == NULL)
	{
		return false;
	}

	if(strcmp(password.c_str(), _mp_row[1])!=0)
	{
		return false;
	}
	return true;
}
bool Cmysql::inserttosql(string id, string name, string sex, int findtime, int keeptime)
{
	char cmd[100] = {"insert into tourist values('"};
	sprintf(cmd + strlen(cmd), "%s','%s','%s','%d','%d');", id.c_str(), name.c_str(), sex.c_str(), findtime, keeptime);
	
	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		printf("cmd query fail\n");
		return false;
	}
	return true;
}
bool Cmysql::deletefromsql(string id)
{
	char cmd[100] = {"delete from "};
	sprintf(cmd + strlen(cmd), "tourist where id='%s';", id.c_str());
	
	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		printf("cmd query fail\n");
		return false;
	}
	_mp_res = mysql_store_result(_mpcon);
	if(_mp_res == NULL)
		return false;
	return true;
}
bool Cmysql::updatefromsql(int choice, string id, string str)
{
	char cmd[100] = {"update tourist set "};
	if(choice == 1)
	{
		sprintf(cmd + strlen(cmd), "name='%s' where id='%s'", str.c_str(), id.c_str());
	}
	if(choice == 2)
	{
		sprintf(cmd + strlen(cmd), "id='%s' where id='%s'", str.c_str(), id.c_str());
	}
	if(choice == 3)
	{
		sprintf(cmd + strlen(cmd), "sex='%s' where id='%s'", str.c_str(), id.c_str());
	}
	if(choice == 4)
	{
		sprintf(cmd + strlen(cmd), "findtime=%s where id='%s'", str.c_str(), id.c_str());
	}
	if(choice == 5)
	{
		sprintf(cmd + strlen(cmd), "keeptime=%s where id='%s'", str.c_str(), id.c_str());
	}
	
	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		return false;
	}
	_mp_res = mysql_store_result(_mpcon);
	if(_mp_res == NULL)
		return false;
	return true;
}
bool Cmysql::selectfromsql(string id)
{
	char cmd[100] = {"select *from tourist where id='"};
	sprintf(cmd + strlen(cmd), "%s';", id.c_str());

	if(mysql_real_query(_mpcon, cmd, strlen(cmd)))
	{
		return false;
	}

	_mp_res = mysql_store_result(_mpcon);
	_mp_row = mysql_fetch_row(_mp_res);
	if(_mp_row == NULL)
	{
		return false;
	}
	return true;

}


#endif
