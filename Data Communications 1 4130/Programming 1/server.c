/************************************************************************/
/* Server running a pared down version of HTTP/1.0                      */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* contains data types used in system calls */
#include <sys/socket.h> /* definitions and structures needed for sockets */
#include <netinet/in.h> /* constants and structures needed for internet domain addresses  */

#define LENGTH 512

/* perror prints an error message pertaining to the last error encountered during a system of library function.  Since msg is not an null string, the msg is printed, a colon, followed by a space and default error message for that syscall/function.  */
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv)
{
	/* socket file descriptor and new socket file descriptor are used as array subscripts into the file descriptor table.  These variables store the values returned by the socket system call and the accept system call.  port_number stores the port number on which the server accepts connection. n is the return value for read() and write() calls */
	int sock_file_desc, new_sock_file_desc, port_number, n;
	/* client_addr_len stores the size of the address for the client, required for accept system call */
	socklen_t client_addr_len;	
	/* buffer characters read in from the socket */
	char buffer[LENGTH];
	/* struct sockaddr_in is the structure containing the internet address, defined in netinet.h
	struct sockaddr_in
	{
		short sin_family; // address family: AF_INET
		u_short sin_port; // port in network byte order
		struct in_addr sin_addr; // internet address
		char sin_zero[8]; // not used but must be zeros
	}
	*/	
	struct sockaddr_in serv_addr, cli_addr;
	/* if user enter invalid number of command line arguments, an error message will be displayed with an error number 1 */
	if (argc < 2) {
		fprintf(stderr, "Error: No port number provided\n");
		exit(1);
	}
	/* The socket system call creates a new socket.  The first argument specified the communication domain, in our case we're using IPv4 Internet Protocols.  The second argument is the indicated type, which specifies the communication semantics.  SOCK_STREAM provides a sequenced, reliable, connection-based stream, and an out-of-band data transmission mechanism may be supported. The third argument is the protocol, we normally choose 0 for the protocol because this allows the operating system to choose the most appropriate protocol (eg: TCP for SOCK_STREAM and UDP for STOCK_DGRAM.) */	
	sock_file_desc = socket(AF_INET, SOCK_STREAM, 0);
	/* The socket system call will return an entry into the file descriptor table.  If the socket system call fails, it returns -1. */
	if (sock_file_desc < 0) 
		error("Error: cannot open socket\n");
	/* pass memset a pointer to the buffer serv_address and fill in the assign all the values as zero */
	memset((char*) &serv_addr, '\0', sizeof(serv_addr));
	/* obtain the port number from arguments */
	port_number = atoi(argv[1]);
	/* assign the address family for the server address is assigned to AF_INET(IPv4) */
	serv_addr.sin_family = AF_INET;
	/* the sin_addr field is a struct in_addr which only contains one field 'unsigned long s_addr'.  This field contains the IP address of the server host, which is the IP address of the server machine. The constant INADDR_ANY retrieves the IP address that the server machine is running on. */
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	/* the sin_port field takes the port number after it has been converted to network byte order.  Computer networks are Big Endian, this means that when little endian computers are going to pass integers over the network, they need to convert them to network byte order.  htons(host to network short) takes the port number and converts host byte order to a network byte order short integer. */
	serv_addr.sin_port = htons(port_number);
   /* the bind() system call assigns an address to a socket.  We include the address of the current host and the port number our server will run on.  The first argument is the socket file descriptor, the second argument is a pointer to our struct sockaddr_in which is cast as struct_addr because they are essentially the same thing.  Bind may fail if the socket is already in use on the machine. */
	if ( bind( sock_file_desc, (struct sockaddr *) &serv_addr, sizeof(serv_addr) ) < 0 )
		error("ERROR binding failed");
	/* the listen() system call allows our server to listen to the socket connection for an event.  First argument is the socket file descriptor, and the second is the backlog parameter that defines the maximum length the queue of pending connections may grow to.  If a connection request arrives with the queue full, the client will receive an error */
	listen(sock_file_desc, 5);
	client_addr_len = sizeof(cli_addr);
	/* int accept(int s, struct sockaddr *addr, int *addrlen) is a system call that extracts the first connection on the queue of pending connections, creates a new socket with the same properties of s and allocates a new file descriptor for the socket.  The accepted socket is now connected to our socket and allows them to communicate.  The addr argument is a result parameter that is filled in with the address of the connecting entity, as known to the communications layer.  The exact format of the addr parameter is determined by the domain in which the communication is occurring.  The int addrlen is also passed in by reference and the value which intially contained the byte length of the *addr, will now contain the actual byte length of the address returned.  This call is used in association with connection-based socket types, currently with SOCK_STREAM. */
	new_sock_file_desc = accept( sock_file_desc, (struct sockaddr *) &cli_addr, &client_addr_len );
	if (new_sock_file_desc < 0)
		error("ERROR accept failed");
	/* initialize buffer with all zeros. */
	bzero(buffer, LENGTH);
	/* read in from the new socket using the new file descriptor.  read() will block until there is actually content to read from the socket. */
	n = read(new_sock_file_desc, buffer, (LENGTH-1));
	if (n < 0)
		error("ERROR reading from socket");
	
	if ( strcmp(buffer, "GET") == 0 )
	{
		
	}
	else if ( strcmp(buffer, "PUT") == 0 )
	{
		
	}


	/* we can write back to the connecting client socket using the write system call.  We use the new socket file descriptor again and for the last argument we need to input the actual size of the message. */
	n = write(new_sock_file_desc, "I got your message", 18);
	if (n < 0)
		error("ERROR writing to socket");
	/* before the process ends, we need to remove both socket file descriptors. */
	close(new_sock_file_desc);
	close(sock_file_desc);
	return 0;
}
