#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>		//inet_addr
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

     int socket_desc;
     struct sockaddr_in server;
     char *message, *server_reply;


	//create socket
	socket_desc= socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc== -1)
	{
	  printf("could not create socket");
	}

	server.sin_addr.s_addr= inet_addr("192.168.43.44"); 	//My VM server ip address
	server.sin_family= AF_INET;
	server.sin_port= htons(8888);

	//connect to remote server
	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{

	    puts("sambungan remote server gagal");
	    return 1;
	}

	 puts("berjaya buat sambungan remote server\n");

	//menghantar data
	message="connect";
	if( send(socket_desc, message, strlen(message), 0) < 0)
	{
	    puts("penghantaran gagal");
	    return 1;
	}

	puts("Data berjaya dihantar\n");

	//Terima balasan daripada server


	if(recv(socket_desc, server_reply, 2000, 0) < 0)
	{
	  puts("Tak dapat reply daripada server");
	}

	puts("dapat balasan daripada server, yeay!!\n");

	puts(server_reply);
	return 0; 
	
}

