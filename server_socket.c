#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>		//inet_addr
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  int socket_desc, new_socket, c;
  struct sockaddr_in server, client;

	//create socket
      socket_desc=socket(AF_INET, SOCK_STREAM, 0);

      if(socket_desc == -1)
      {
	   printf("tak boleh buat socket");
      }

	//Prepare the sockaddr_in structure

       server.sin_family= AF_INET;
       server.sin_addr.s_addr= INADDR_ANY;
       server.sin_port= htons(8888);

		//BIND
       if( bind(socket_desc,(struct sockaddr*)&server, sizeof(server)) <0)
       {
	   puts("bind tak berjaya");
       }

       puts("bindd berjaya!");

		//LISTEN
	listen(socket_desc, 3);

		//Accept and incoming connetion
	puts("menunggu incoming connections....");
	c= sizeof(struct sockaddr_in);

	new_socket=accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if(new_socket<0)
	{
	  perror("accepted failed");
	}

	puts("Sambungan diterima");
	return 0;
}
