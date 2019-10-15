#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#include<math.h>

#define MAXLEN 65535
#define PORT 8099
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628

void main(){

	int server_fd, sock_fd;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	if( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
        exit(EXIT_FAILURE);
	}

	if( setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	{
		perror("setsockopt");
        exit(EXIT_FAILURE);
	}

	memset(&address, 0, addrlen);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
   	{
        	perror("bind failed");
        	exit(EXIT_FAILURE);
   	}

    if(listen(server_fd, 3) < 0)
    {
    	perror("listen");
    	exit(EXIT_FAILURE);
    
	}
    if ((sock_fd = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
   	{
        perror("accept");
        exit(EXIT_FAILURE);
    }

	int len;

/*
	//Message Transfer

	char readBuffer[MAXLEN];
	char sendBuffer[MAXLEN];
    len = read(sock_fd, &readBuffer, MAXLEN);
    printf("received : %s\n\nEnter Message : ", readBuffer);
	scanf("%s" , sendBuffer);
	send(sock_fd  , sendBuffer , MAXLEN , 0 );
	printf("Message Sent\n");



	//File transfer
	
	char fileName[256];

	len = read(sock_fd, fileName, MAXLEN);
	FILE *fp;

	printf("file Name %s\n\n" , fileName);
	
	fp = fopen( fileName, "w+");
	char buffer2[MAXLEN];
	len = recv(sock_fd, buffer2, MAXLEN, 0);
	//printf("%s\n%d\n",buffer2,len);
	//fwrite(buffer2,MAXLEN,1,fp);
	int i;
	for( i = 0 ; buffer2[i] != 0 ;i++)
	{
		fprintf(fp ,"%c" , buffer2[i]);
	}
	//fprintf(fp,"\0");
	printf("File Received\n\n");
	fclose(fp);

*/


	// Trigonometric Calculator

	int recv, option, angle, answer;
	len = read(sock_fd, &recv, sizeof(recv));
	option = ntohl(recv);
	len = read(sock_fd, &recv, sizeof(recv));
	angle = ntohl(recv);

	//printf("%d, %d ", option, num1);

	switch(option){
		case 1:
			answer = sin(PI*angle/180.0)*1000000;
			break;
		case 2:
			answer = cos(PI*angle/180.0)*1000000;
			break;
		case 3:
			answer = tan(PI*angle/180.0)*1000000;
			break;
		default:
			answer = 0;
			break;
	}
	printf( "%d" , answer);
	recv = htonl(answer);
	send(sock_fd, &recv, sizeof(recv), 0);

}
