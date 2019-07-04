/*************************************************************************
    > File Name: main.cpp
    > Created Time: Sat 12 Jan 2019 11:34:40 AM CST
 ************************************************************************/
#include<iostream>
#include"banlance.h"
#include"hashlist.h"
using namespace std;


int main()
{
	hashlist::gethashlist();
	int client_server, server_server;
	cout<<"please input the client_server's port:"<<endl;
	cin>>client_server;
	cout<<"please input the server_server's port:"<<endl;
	cin>>server_server;
	banlance ban(client_server, server_server);
	ban.run();
	return 0;
}
