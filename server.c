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

  //////////////////////////////////////////////
  int arr_size = 51;
  int arr[arr_size];// create array of 51 cards
  for (int i = 0; i < arr_size; i++) {
    arr[i] = i+1;
    printf("value at index %u: %u\n", arr[i], arr[i]);
  }
  
  randperm((int *)arr, arr_size);//shuffle the array 
  
  printf("\nafter randperm :\n\n"); 
  
  for (int i = 0; i < arr_size; i++) {
    printf("value at index %u: %u\n", i+1, arr[i]);
  }
  char buff[100]; //contains integer
  //////////////////////////////////////////////
  
  
	char *hello = "hello from the server"; 
  int socketfd, addrlen, n;
  socketfd = socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in addr; //one for server (addr), one for incoming connection(add_c)
  addr.sin_family = AF_INET; //AF_INET --> ipv4
  addr.sin_addr.s_addr = htonl(INADDR_ANY); //will accept connections from any client IP address
  addr.sin_port = htons(PORT); // specify port 
  //htons function makes sure that numbers are stored in memory in network byte order (little endian in this case)
  

  addrlen = sizeof(addr);
  

  //bind(socketfd, addr, addrlenO);
 // bind(socketfd, (struct sockaddr *)&addr, addrlen);
  if ( bind(socketfd, (struct sockaddr *)&addr, addrlen) < 0){
  	printf("error");
  	}
  	
  int backlog = 2;
  //listen(socketfd, backlog);
  if( listen(socketfd, backlog) < 0){
  	printf("error");
  	}
  
   
  //struct created for client (incoming connection) 	
  struct sockaddr_in add_c;
  int c_len = sizeof(add_c); //address length for the incoming connection
  
  //parameters for send function
  int flag = 0;
  size_t size = strlen(hello); 

  while(1){
    //accept(socketfd, (struct sockaddr *)&add_c, &c_len); 
    int confd = accept(socketfd, (struct sockaddr *)&add_c, &c_len);
    if ( confd < 0){
    	printf("errors");
    	}
    	
  /*//read from client : 
    read (confd, buff, sizeof(buff));
    printf("From client: %s \n", buff);*/
    
    /*
    send(confd, hello, size,flag);
    printf("test message sent\n"); */

    
    //deal one card to client until the deck is exhasted/*
    for (int i = 0; i < arr_size; i++) {
      int card_num = i + 1;
      printf("sending card %u: %u\n", card_num, arr[i]);  
           
      //write to and and send the buffer to client    
        
      sprintf(buff, "card %u: %u \n", card_num, arr[i]);
      size_t size_int = strlen(buff); 
      send(confd, buff, size_int,flag);
    } 
    break;
  }
  return 0;
}

