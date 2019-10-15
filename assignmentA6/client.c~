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
#define PORT 8099
#define MAXLEN 65535

void main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, "192.168.0.101", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
       
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        
    }

    int len;


    //message Transfer
    char readBuffer[MAXLEN];
    char sendBuffer[MAXLEN];

    printf("Enter Message : ");
    len = scanf("%s" , sendBuffer);
    send(sock  , sendBuffer , MAXLEN , 0 );
    printf("Message sent\n\n");
    len = read(sock, &readBuffer, MAXLEN);
    printf("received : %s\n", readBuffer);
    
/*
    // File transfer
    
    char fileName[256];
    printf("Enter File Name : ");
    scanf("%s" , fileName);

    FILE *fp;
    fp = fopen(fileName, "r");
    fseek(fp, 0, SEEK_END);
    int fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char buffer2[fsize];
    
    fread(buffer2, fsize , 1, fp);
    
    send(sock, fileName, 256, 0);
    send(sock, buffer2, fsize, 0);

    printf("File Sent\n\n");

    fclose(fp);


    // Trigonometric Calculator
    
    printf("\n[1]To Find SIN\n[2]To Find COS\n[3]To Find TAN\n >");
    int option;
    scanf("%d", &option);
    int converted = htonl(option);
    
    send(sock, &converted, sizeof(converted), 0);
    
    printf("Enter Angle (Degree) : ");
    int num1;
    scanf("%d", &num1);
    converted = htonl(num1);
    send(sock, &converted, sizeof(converted), 0);
    
    int valread2 = read(sock, &converted, sizeof(converted));
    float answer = ntohl(converted)/1000000.0;
    printf("Answer : %f\n", answer);
*/    

}
