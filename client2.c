
#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<sys/socket.h>

#include<sys/types.h>

#include<unistd.h>

#include<netinet/in.h>

#define PORT 6666
int main(int argc,char **argv)

{
	int sockfd;
	int err,n;
	struct sockaddr_in addr_ser;
	char sendline[4][20],recvline[20];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("socket error\n");
		return -1;
	}
	bzero(&addr_ser,sizeof(addr_ser));
	addr_ser.sin_family=AF_INET;
	addr_ser.sin_addr.s_addr=htonl(INADDR_ANY);
	addr_ser.sin_port=htons(PORT);
	err=connect(sockfd,(struct sockaddr *)&addr_ser,sizeof(addr_ser));
	if(err==-1)
	{
		printf("connect error\n");
		return -1;
	}
	printf("登陆到服务器上\n");
	while(1)
	{
		for(int i=0;i<4;i++)
	  {
		scanf("%s",sendline[i]);
		send(sockfd,sendline[i],strlen(sendline[i]),0);
	  }	
		for(int j=0;j<4;j++)
	  {
		char new[6];
		for(int i=0;i<6;i++)
		{
			new[i]=sendline[j][i];
		}
		new[6]='\0';
		if(strcmp(new,"finish")==0) 
			{
				exit(0);		
			}
		printf("等待服务器处理..\n");
	    n=recv(sockfd,recvline,100,0);
		recvline[n]='\0';
       if(strcmp(recvline,"succeed-return-0")==0) printf("0\n");
	   else printf("1\n");
	 }
	 printf("办理结束\n");
  }		
	close(sockfd);
	return 0;					
}
