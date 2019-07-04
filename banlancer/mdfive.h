/*************************************************************************
    > File Name: mdfive.h
    > Created Time: Fri 11 Jan 2019 08:25:18 PM CST
 ************************************************************************/
#ifndef __MDFIVE_H
#define __MDFIVE_H
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<openssl/md5.h>
using namespace std;

class mdfive
{
private:
	string _ip;
	int _port;
	int _num;
	MD5_CTX _ctx;
	unsigned char outmd[16];
	long _hash;
public:
	mdfive(string ip, int port)
	{
		_ip = ip;
		_port = port;
		memset(outmd, 0, 16);
		_num = -1;
		MD5_Init(&_ctx);
	}
	~mdfive() {}
	mdfive(string ip, int port, int num)
	{
		_ip = ip;
		_port = port;
		_num = num;
		memset(outmd, 0, 16);
		MD5_Init(&_ctx);
	}
	void usemd()
	{
		char all[20] = {0};
		sprintf(all, "%d%d", _port, _num);
		_ip = _ip + all;
		MD5_Update(&_ctx, _ip.c_str(), _ip.size());
		
		MD5_Final(outmd, &_ctx);
		for(int i = 0; i < 4; i++)
		{
			_hash+=((long)(outmd[i*4+0]&0xFF)
					|(long)(outmd[i*4+1]&0xFF)<<8
					|(long)(outmd[i*4+2]&0xFF)<<16
					|(long)(outmd[i*4+3]&0xFF)<<24);
		}
	}
	long getmdnum()
	{
		return _hash;
	}
};

#endif
