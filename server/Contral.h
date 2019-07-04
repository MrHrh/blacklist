/*************************************************************************
    > File Name: Contral.h
    > Created Time: Sat 15 Dec 2018 07:34:54 PM CST
 ************************************************************************/
#ifndef __CONTRAL_H
#define __CONTRAL_H

#include<iostream>
#include"Model.h"
#include"public.h"
#include<json/json.h>
using namespace std;

class contral
{
public:
	contral()
	{
		_model = new model();
	}
	void process(int fd, Json::Value val)
	{
		cout<<"process"<<endl;
		int choice = val["type"].asInt();
		_model->get_view(choice)->view_handle(fd, val);
	}
private:
	model *_model;
};

#endif
