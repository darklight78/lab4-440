#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;
	int optval;
	socklen_t optlen =sizeof(optval);

	//create socket
	socket_desc= socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("could not create socket");
	}

	/* check the status for the keepalive option */

	if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval,&optlen) < 0)
	{
		perror("getsockopt()");
		close(socket_desc);
		exit(EXIT_FAILURE);
	}

	printf("SO_KEEPALIVE is %s\n", (optval ? "ON":"OFF"));

	/*set the option acive*/

	optval= 1;
	optlen= sizeof(optval);

	if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0)
	{
		perror("setsockopt()");
		close(socket_desc);
		exit(EXIT_FAILURE);
	}

	printf("SO_KEEPALIVE set on socket\n");

	/*check the status again*/

	if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0)
	{
		perror("getsockopt()");
		close(socket_desc);
		exit(EXIT_FAILURE);
	}

	printf("SO_KEEPALIVE is %s\n", (optval? "ON":"OFF"));

	//prepare the sockaddr in structure
	server.sin_family= AF_INET;
	server.sin_family= INADDR_ANY;
	server.sin_port= htons(8888);

	//Bind
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("bind gagal");
		return 1;
	}

	puts("bind berjaya");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection

	puts("menunggu incoming connection...");
	c =sizeof(struct sockaddr_in);

	 while( (new_socket=accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	 {

		puts("connection diterima");

		//reply to the client
		message="Hello client, i have received your connetion. But i have to go now,bye\n";

		write(new_socket, message, strlen(message));
	 }

	if(new_socket < 0)
	{
		perror("accepted failed");
		return 1;
	}

	return 0;
}

