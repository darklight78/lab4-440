#include <stdio.h>
#include <string.h>		//strlen
#include <sys/socket.h>
#include <arpa/inet.h>		//inet_addr
#include <unistd.h>		//write

int main(int argc, char *argv[])
{

	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;

	//create socket

	socket_desc= socket(AF_INET,SOCK_STREAM, 0);

	if(socket_desc == -1)
	{
		printf("tak boleh buat socket");
	}

	//prepare the sockaddr_in structure

	server.sin_family= AF_INET;
	server.sin_addr.s_addr= INADDR_ANY;
	server.sin_port= htons( 8888);

	//Bind
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind gagal");
		return 1;
	}

	puts("bind berjaya!");

	//listen
	listen(socket_desc, 3);

	//Accept incoming connection

	puts("menunggu incoming connection...");
	c= sizeof(struct sockaddr_in);

	 while( (new_socket= accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	  {
		puts("connection diterima");

		//reply to the client

		message= "hello client, saya terima connection, now saya pergi dulu, bye\n";
		write(new_socket, message, strlen(message));
	  }

	if(new_socket < 0)
	{
		perror("accept gagal ;[");
		return 1;
	}

	return 0;
}

