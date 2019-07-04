/*************************************************************************
    > File Name: hashlist.h
    > Created Time: Fri 11 Jan 2019 08:46:39 PM CST
 ************************************************************************/
#ifndef __HASHLIST_H
#define __HASHLIST_H

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<map>
#include<pthread.h>
using namespace std;

pthread_mutex_t m;

class hashlist
{
private:
	static hashlist* _list;
	map<long, long>_hashmap;
	hashlist()
	{
	}
public:
	static hashlist *gethashlist()
	{
		if(_list == NULL)
		{
			pthread_mutex_lock(&m);
			if(_list == NULL)
			{
				_list = new hashlist();
			}
			pthread_mutex_unlock(&m);
		}
		return _list;
	}
	long addtoarr(long hash)
	{
		_hashmap.insert(make_pair(hash, hash));
		return hash;
	}	

	long findvnode(long hash)
	{
		map<long, long>::iterator it = _hashmap.lower_bound(hash);
		if(it == _hashmap.end())
		{
			it = _hashmap.begin();
			it = _hashmap.lower_bound(hash);
		}
		return it->second;
	}

	void erasekey(long hash)
	{
		_hashmap.erase(hash);
	}
};

hashlist* hashlist::_list = NULL;

#endif
