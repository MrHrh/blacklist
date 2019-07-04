/*************************************************************************
    > File Name: main.cpp
    > Created Time: Fri 07 Dec 2018 02:09:01 PM CST
 ************************************************************************/

#include<iostream>
#include"Csys.h"
#include"CthreadPool.h"
using namespace std;

int main()
{
	Csys* mysys = new Csys();
	mysys->run();
	return 0;
}


