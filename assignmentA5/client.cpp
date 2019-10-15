#include<bits/stdc++.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
using namespace std;

#define LPORT 6000
#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;

	struct sockaddr_in servaddr;
	
	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0 )
	{
		perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}
	
	servaddr.sin_family = AF_INET;
   	servaddr.sin_port = htons(LPORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));


	string fileName;
	int len;

	char  *buffer;

	cout<<"Enter File Name : ";
	cin>>fileName;

	ifstream infile;
	infile.open( fileName.c_str() , ios::ate | ios::binary );
	int fileSize = infile.tellg();
	infile.seekg(0);
	buffer = new char[fileSize];
    infile.read(buffer, fileSize);

	len = sendto(sockfd, (const char *)fileName.c_str() , fileName.length() , 0 , (const struct sockaddr *) &servaddr, sizeof(servaddr));
   	len = sendto(sockfd, (const char *)buffer, fileSize , 0 , (const struct sockaddr *) &servaddr, sizeof(servaddr));
    
	cout<<"File Sent"<<endl;

    close(sockfd);
    infile.close();
	return 0;
}

