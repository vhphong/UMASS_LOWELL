#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define LENGTH 512

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char **argv)
{
	int sockfd, port_number, n;
	/*
	struct sockaddr_in 
	{
		short sin_family; // address family: AF_INET
		u_short sin_port; // port in network byte order
		struct in_addr sin_addr; // internet address
		char sin_zero[8]; // not used but must be zero	
	} */
	struct sockaddr_in serv_addr;
	/* 
	struct hostnet
	{
		char *h_name;  // "official" name of the host
		char **_aliases;  // alternative names for the host, represented as a null-terminated vector of string
		int h_addrtype;  // host address type; AF_INET or AF_INET6(IPv6 hosts)
		int h_length;  // the length, in bytes, of each address
		char **h_addr_list; // vector of addresses for the host (the host might be connected to multiple networks and have different addresses for each one). Null terminated
		#define h_addr h_addr_list[0]  // The first host address
	};	*/
	struct hostent *server;		
	/* print to standard error stream if invalid number of arguments are entered in console */
	if (argc < 5) {
		fprintf(stderr, "usage %s hostname port_number (GET or PUT) filename\n", argv[0]);
		exit(0);
	}
	/* get the port number from console line argument */
	port_number = atoi(argv[2]);
	/* The socket(int domain, int type, int protocol) system call creates an endpoint for communication and returns a descriptor. AF_INET uses the IPv4 protocol and we use a sock_stream which is continuous stream as if from a file or a pipe.The default third argument for socket is 0 because it allows the operating system to decide the protocol. */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* if socket fails, it will return -1 */
	if (sockfd < 0)
		error("ERROR opening socket");
	/* obtain the name of the host on the internet, eg: localhost */
	server = gethostbyname(argv[1]);
	if(server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port_number);
	if (connect( sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	n = write(sockfd, argv[3], strlen(argv[3]));
	if ( n < 0 )
		error("ERROR writing to socket");
	n = write(sockfd, argv[4], strlen(argv[4]));
	if( n < 0 )
		error("ERROR writing to socket");
	
	char buffer[LENGTH];
	bzero(buffer, LENGTH);

	if ( strcmp(argv[3], "GET") == 0 )
	{
	}
	else if( strcmpargv([3], "PUT") == 0)
	{
		FILE *fp = fopen(argv[4], "r");
		if (fp == NULL)
		{
			printf("ERROR: File %s no found.\n", argv[4]);
			exit(-1);
		}
		size_t nbytes = 0;
		while ( (nbytes = fread(buffer, sizeof(char), LENGTH)) > 0 )
		{
			n = write
		}			
	}
	else
	{
		fprintf(stderr, "usage %s hostname port_number (GET or PUT) filename\n", argv[0]);
	}
	close(sockfd);
	return 0;
}
