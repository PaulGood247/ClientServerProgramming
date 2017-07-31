#include "unp.h"
#include <time.h>
#include <stdio.h>

int main (int argc, char ** argv)
{
	int n, listenfd, connfd, char_in, count=0;
	struct sockaddr_in servaddr;
	char wbuff[MAXLINE],rbuff[MAXLINE], cmd[16], path1[64]={"."}, path[64], vers[16];
	FILE * hFile;

	if (argc !=2)
		err_quit("usage: a.out <Port>");

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

		while((n=read(connfd, rbuff, MAXLINE))>0)
		{
			rbuff[n]=0;

			if(fputs(rbuff, stdout)==EOF)
				err_sys("fputs error");

			if((strstr(rbuff,"\r\n\r\n"))>0)
				break;
		}

		if (n <0)
			err_sys("read error");

		sscanf(rbuff, "%s %s %s", cmd , path , vers);

		strcat(path1, path);

		if(strcmp(path1, "./")==0)
		{
			strcpy(path1, "./index.html");
		}

		hFile=fopen(path1, "r");

		if(hFile ==NULL)
		{
			hFile = fopen("error.html", "r");
		}

		strcpy(wbuff, "");

		while((char_in = fgetc(hFile))!=EOF)
		{
			wbuff[count]=char_in;
			count++;
		}
		wbuff[count]=0;
		Write(connfd , wbuff, strlen(wbuff));
		count=0;
		fclose(hFile);
		strcpy(path1, ".");

		Close(connfd);
	}
	
}

