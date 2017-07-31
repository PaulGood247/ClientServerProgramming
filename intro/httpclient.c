#include "unp.h"

int 
main(int argc, char **argv)
{
	int sockfd, n , counter=0;
	char recvline[MAXLINE +1],  writebuff[MAXLINE];
	struct sockaddr_in servaddr;

	if (argc!=4)
		err_quit("usage: ./httpclient <ipaddress> <portno.> <resource>");

	if ((sockfd=socket(AF_INET, SOCK_STREAM,0))<0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[2]));
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr))<0)
		err_sys("connect error");

	snprintf(writebuff, sizeof(writebuff), "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[3], argv[1]);
	Write(sockfd , writebuff, strlen(writebuff));
	
	while((n =read(sockfd, recvline, MAXLINE))>0){
		counter++;
		recvline[n]=0;
		if(fputs(recvline, stdout)==EOF)
			err_sys("fputs error");
	}
	if(n<0)
		err_sys("read error");
	printf("counter = %d\n", counter);

	exit(0);
}
