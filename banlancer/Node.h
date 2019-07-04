/*************************************************************************
    > File Name: Node.h
    > Created Time: Fri 11 Jan 2019 07:01:09 PM CST
 ************************************************************************/
#ifndef __NODE_H
#define __NODE_H

#include<iostream>
#include<map>
#include"virtualnode.h"
using namespace std;

class Node
{
private:
	string _ip;
	int _port;
	int _count;
	virtualnode* _vnode;
	map<int, int>_vnodemap;
	map<int, virtualnode*>_vmap;
public:
	Node(string ip, int port, int count)
	{
		_ip = ip;
		_port = port;
		_count = count;
		_vnode = NULL;
	}
	~Node()
	{
		map<int, virtualnode*>::iterator it = _vmap.begin();
		for(; it != _vmap.end(); it++)
		{
			it->second->~virtualnode();
		}
	}
	void createvnode()
	{
		int i = 0;
		for(; i<_count; i++)
		{
			_vnode = new virtualnode(_ip, _port, i);
			if(NULL == _vnode)
			{
				cout<<"create virtual node fail"<<endl;
				return;
			}
			_vmap.insert(make_pair(i, _vnode));
			_vnode->hashvirtualnode();
			_vnodemap.insert(make_pair(i, _vnode->getindex()));
		}
	}
	bool isindex(long index)
	{
		for(int i=0; i<_count; i++)
		{
			if(_vnodemap[i] == index)
				return true;
		}
		return false;
	}
	void getaddress(string &ip, int &port)
	{
		ip = _ip;
		port = _port;
	}
};

#endif
