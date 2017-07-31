#include "unp.h"
#include <time.h>

int main (int argc, char ** argv)
{
	int listenfd, connfd, n;
	struct sockaddr_in servaddr;
	char buff[MAXLINE], recvline[MAXLINE], cmd[10], path[30], vers[10];

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
		

		if((strstr(recvline, "\r\n\r\n"))!=NULL)
			break;

		

	}

		printf("\nExited loop\n");
		sscanf(recvline, "%s %s %s",  cmd, path, vers);

		if(strcmp(path, "/index.html")==0){
			FILE *f;
			size_t len;
			char *line;

			f= fopen("./index.html", "r");

			while(line = fgetc(f, &len)){
				snprintf(buff, sizeof(buff), line);
			}
		}

			//snprintf(buff, sizeof(buff), "HTTP/1.1 200 page found\r\nConnection: close\r\n\r\n<html><Head>Hi there</Head></html>\r\n\r\n");
		else
			snprintf(buff, sizeof(buff), "HTTP/1.1 404 page not found\r\nConnection: close\r\n\r\n<html><Head>Get lost</Head></html>\r\n\r\n");
		
		Write(connfd, buff, strlen(buff));
		Close(connfd);
	}
	
}

