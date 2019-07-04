/*************************************************************************
    > File Name: virtualnode.h
    > Created Time: Fri 11 Jan 2019 08:06:43 PM CST
 ************************************************************************/
#ifndef __VIRTUALNODE_H
#define __VIRTUALNODE_H

#include<iostream>
#include<string>
#include"mdfive.h"
#include"hashlist.h"
using namespace std;

class virtualnode
{
private:
	string _realip;
	int _realport;
	int _count;
	long _index;
public:
	virtualnode(string ip, int port, int count)
	{
		_realip = ip;
		_realport = port;
		_count = count;
	}
	~virtualnode()
	{
		hashlist::gethashlist()->erasekey(_index);
	}
	void hashvirtualnode()
	{
		mdfive* _md = new mdfive(_realip, _realport, _count);
		if(_md == NULL)
		{
			cout<<"one virtualnode get md5 fail"<<endl;
		}
		_md->usemd();
		long mdnum = _md->getmdnum();
		_md->~mdfive();

		_index = hashlist::gethashlist()->addtoarr(mdnum);
	}
	long getindex()
	{
		return _index;
	}
};

#endif
