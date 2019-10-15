/* Client*/
 #include <stdio.h>   /* Standard input/output definitions */
 #include <string.h>  /* String function definitions */
 #include <unistd.h>  /* UNIX standard function definitions */
 #include <fcntl.h>   /* File control definitions */
 #include <errno.h>   /* Error number definitions */
 #include <termios.h> /* POSIX terminal control definitions */

 
//  sudo chmod a+rw /dev/ttyS0  
/*
  * 'open_port()' - Open serial port 1.
  *
  * Returns the file descriptor on success or -1 on error.
  */

 int open_port(void)
 {
   int fd;                                   /* File descriptor for the port */


   fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

   if (fd == -1)
   {                                              /* Could not open the port */
     fprintf(stderr, "open_port: Unable to open /dev/ttyS0 - %s\n",
             strerror(errno));
   }
   else
        printf(" Port Opened Successfully\n");

   return (fd);
 }

void main()
{
 int mainfd=0,n=0;                                            /* File descriptor */
 char chout;
 struct termios options;
   
 mainfd = open_port();

 fcntl(mainfd, F_SETFL, FNDELAY);                  /* Configure port reading */
                                     /* Get the current options for the port */
 tcgetattr(mainfd, &options);
 cfsetispeed(&options, B9600);                 /* Set the baud rates to 9600 */
 cfsetospeed(&options, B9600);
    
                                   /* Enable the receiver and set local mode */
 options.c_cflag |= (CLOCAL | CREAD);
 options.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
 options.c_cflag &= ~CSTOPB;
 options.c_cflag &= ~CSIZE;
 options.c_cflag |=  CS8;                              /* Select 8 data bits */
 options.c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */  
 
                                 /* Enable data to be processed as raw input */
 options.c_lflag &= ~(ICANON | ECHO | ISIG);
       
                                        /* Set the new options for the port */
 tcsetattr(mainfd, TCSANOW, &options);
                         
 while (1)
 {
   n=read(mainfd, &chout, sizeof(chout));          /* Read character from ABU */
  /* if(n==0) printf("\n No User Input");
   else 
        printf("User input =%d",n);*/
   if (chout != 0)
      printf("Got %c.\n", chout);

   chout=0;
   //usleep(2000);
 }
                                                    /* Close the serial port */
  close(mainfd);
 }
