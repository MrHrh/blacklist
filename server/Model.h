/*************************************************************************
    > File Name: Model.h
    > Created Time: Sat 15 Dec 2018 07:51:16 PM CST
 ************************************************************************/
#ifndef __MODEL_H
#define __MODEL_H
#include<iostream>
#include<json/json.h>
#include<map>
#include"view.h"
#include"public.h"
using namespace std;

class model
{
public:
	model()
	{
		mymap.insert(make_pair(LOGIN, new view_login));
		mymap.insert(make_pair(REGISTER, new view_register));
		mymap.insert(make_pair(SELECT, new view_select));
		mymap.insert(make_pair(INSERT, new view_insert));
		mymap.insert(make_pair(UPDATE, new view_update));
		mymap.insert(make_pair(REMOVE, new view_remove));
	}
	view* get_view(int choice)
	{
		return mymap[choice];
	}
private:
	map<int, view*>mymap;
};

#endif
