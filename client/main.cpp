/*************************************************************************
    > File Name: main.cpp
    > Created Time: Sun 25 Nov 2018 04:05:26 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include"Csys.h"
#include"CworkSer.h"

int main()
{
	CworkSer::getWorkSer();
	Csys* msys = new Csys();
	msys->put();
	return 0;
}


