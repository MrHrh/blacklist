/*************************************************************************
    > File Name: messageget.c
    > Created Time: Fri 28 Dec 2018 07:45:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>



#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
	short port;
	printf("input port:");
	fflush(stdout);
	scanf("%d", &port);
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ser, cli;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int err = connect(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(err != -1);

	while(1)
	{
		printf("please input:");
		fflush(stdout);

		char buff[20] = {0};
		fgets(buff, 20, stdin);
		buff[strlen(buff)-1] = 0;
		if(strncmp(buff, "end", 3)==0)
		{
			break;
		}
		err = send(sockfd, buff, strlen(buff), 0);
		assert(err != -1);
	}

	return 0;
}
