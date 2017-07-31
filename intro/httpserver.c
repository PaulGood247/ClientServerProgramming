#include "unp.h"
#include <time.h>

int main (int argc, char ** argv)
{
	int listenfd, connfd, n;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], recvline[MAXLINE], username[10], password[10];

	if (argc !=2)
		err_quit("usage: <Program Name> <Port No.>");

	listenfd = Socket(AF_INET, SOCK_STREAM , 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));
	
	Bind (listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; )
	{
		connfd =Accept (listenfd, (SA *) NULL, NULL);



	while((n =read(connfd, recvline, MAXLINE))>0){
		recvline[n]=0;
		if(fputs(recvline, stdout)==EOF)
			err_sys("fputs error");
		

		if((strstr(recvline, " "))!=NULL)
			break;

	}

		printf("\nExited loop\n");
		sscanf(recvline, "%s %s",  username, password);

		if(strcmp(username, "admin" && strcmp(password, "pass") ==0)
			snprintf(buff, sizeof(buff), "PROCEED");
		else
			snprintf(buff, sizeof(buff), "DENIED");
		
		Write(connfd, buff, strlen(buff));
		Close(connfd);
	}
	
}

