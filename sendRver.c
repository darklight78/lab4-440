#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char*argv[])
{

	int socket_desc;

	struct sockaddr_in server;
	char *message;

	//create socket
	socket_desc =socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1)
	{
	  printf("socket tak jadi nak buat");
	}

	server.sin_addr.s_addr= inet_addr("192.168.43.44"); //My vm ip address
	server.sin_family= AF_INET;
	server.sin_port= htons(22);

	//connect to remote server

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0)
	{
	    puts("sambungan gagal");
	    return 1;
	}

	puts("Alhamdulilah berjaya membuat sambungan\n");

	//send some data

	  message= "berjaya disambung :]";

	  if(send(socket_desc, message, strlen(message), 0) < 0)
	  {
		puts("Penghantaran tidak berjaya");
		return 1;
	  }

	puts("Data berjaya dihantar:]");
	return 0;
}
