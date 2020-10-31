#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define PORT 8000


int main(int argc, char const *argv[]) 
{ 
	
  if (argc < 2) {
	  printf ("error! not enough arguments \nusage: ./client <IP> <PORT>\n");
	  exit(0);
  }


  int socketfd = socket(AF_INET,SOCK_STREAM,0);
  //(unsigned short)strtoul(argv[1], NULL, 0)
  
  
  struct sockaddr_in addr; //one for server (addr) 
  addr.sin_family = AF_INET; //AF_INET --> ipv4
  addr.sin_addr.s_addr = inet_addr(argv[1]); //will accept connections from any client IP address
  addr.sin_port = htons((unsigned short)strtoul(argv[2], NULL, 0)); // specify port 
  //htons function makes sure that numbers are stored in memory in network byte order (little endian in this case)
  
  int con = connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)); //connect to server
  

  int arr[51];///initialize array to recieve
  char buff[] = "deal";
  
  	
  send(socketfd, &buff, strlen(buff),0); //send to server
  printf("\nmessage sent\n\n");
  recv(socketfd, &arr, 51 * sizeof(int),0); //recieve from server
  	
  	 
	for (int i = 0; i < 51; i++){
  	  printf("\n Card from Server : %d \n", arr[i]);
  	}
  close(socketfd);
}








