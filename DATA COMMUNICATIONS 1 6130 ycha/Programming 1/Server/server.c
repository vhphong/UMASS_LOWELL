/************************************************************************/
/* Server running a pared down version of HTTP/1.0                      */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h> /* contains data types used in system calls */
#include <sys/socket.h> /* definitions and structures needed for sockets */
#include <netinet/in.h> /* constants and structures needed for internet domain addresses  */

#define LENGTH 512

/* socket file descriptor and new socket file descriptor are used as array subscripts into the file descriptor table.  These variables store the values returned by the socket system call and the accept system call. */
int sock_file_desc, new_sock_file_desc;
int signalsToHandle[] = {SIGHUP, SIGINT, SIGQUIT, SIGBUS, SIGTERM, SIGSEGV, SIGFPE};

/* perror prints an error message pertaining to the last error encountered during a system of library function.  Since msg is not an null string, the msg is printed, a colon, followed by a space and default error message for that syscall/function.  */
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

/* close socket file descriptors and exit */
void closeAndExit()
{
   close(new_sock_file_desc);
	close(sock_file_desc);
	exit(0);  
}

/* signal handler */
void handle_signal(int signal)
{
   printf("Signal handler executing..\n");
   closeAndExit();
}

void newConnection();

int main(int argc, char **argv)
{
   /* if user enter invalid number of command line arguments, an error message will be displayed with an error number 1 */
	if (argc < 2) {
		fprintf(stderr, "Error: No port number provided\n");
	}
   sigset_t signalMask;
   struct sigaction sAction;
	/* port_number stores the port number on which the server accepts connection. n is the return value for read() and write() calls */
	int port_number, nSigs, i;
	/* Block these signals in signal handler */
	nSigs = sizeof(signalsToHandle) / sizeof(int);
	sigemptyset(&signalMask);
	for (i = 0; i < nSigs; i++)
	   sigaddset(&signalMask, signalsToHandle[i]);
	sAction.sa_handler = handle_signal;
	sAction.sa_mask = signalMask;
	sAction.sa_flags = 0;
	for (i = 0; i < nSigs; i++)
	{
	   if (sigaction(signalsToHandle[i], &sAction, NULL) == -1)
	   {
	      error("ERROR sigaction: ");
	   }
	}
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
	/* client_addr_len stores the size of the address for the client, required for accept system call */
	socklen_t client_addr_len;	
	client_addr_len = sizeof(cli_addr);
	/* The socket system call creates a new socket.  The first argument specified the communication domain, in our case we're using IPv4 Internet Protocols.  The second argument is the indicated type, which specifies the communication semantics.  SOCK_STREAM provides a sequenced, reliable, connection-based stream, and an out-of-band data transmission mechanism may be supported. The third argument is the protocol, we normally choose 0 for the protocol because this allows the operating system to choose the most appropriate protocol (eg: TCP for SOCK_STREAM and UDP for STOCK_DGRAM.) */	
	sock_file_desc = socket(AF_INET, SOCK_STREAM, 0);
	/* The socket system call will return an entry into the file descriptor table.  If the socket system call fails, it returns -1. */
	if (sock_file_desc < 0) 
		error("Error cannot open socket\n");
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
	
	while (1)
	{
	   /* int accept(int s, struct sockaddr *addr, int *addrlen) is a system call that extracts the first connection on the queue of pending connections, creates a new socket with the same properties of s and allocates a new file descriptor for the socket.  The accepted socket is now connected to our socket and allows them to communicate.  The addr argument is a result parameter that is filled in with the address of the connecting entity, as known to the communications layer.  The exact format of the addr parameter is determined by the domain in which the communication is occurring.  The int addrlen is also passed in by reference and the value which intially contained the byte length of the *addr, will now contain the actual byte length of the address returned.  This call is used in association with connection-based socket types, currently with SOCK_STREAM. */
	   new_sock_file_desc = accept( sock_file_desc, (struct sockaddr *) &cli_addr, &client_addr_len );
	   if (new_sock_file_desc < 0)
		   error("ERROR accept failed");	 
		   
		/* fork every time client has been accepted */   
      int pid = fork();
      switch (pid) 
      {
         case -1:
            perror("fork failed:");
            closeAndExit();  
         case 0:     /* Hand over control to Child process */
            newConnection();
            printf("Child process closing\n");
            closeAndExit();
         default:    /* Parent closes the connection to client socket */
            close(new_sock_file_desc);
            break;
      }  
	}
	
	closeAndExit();
	return 0;
}

/* run PUT or GET operations here */
void newConnection()
{
   int n, write_size, bytesToRead;
	/* buffer characters read in from the socket */
	char buffer[LENGTH];
	char fileName[LENGTH];
	
	printf("Accepted new connection.\n");
	
   /* initialize buffer with all zeros. */
	bzero(buffer, LENGTH);
	/* read in from the new socket using the new file descriptor.  read() will block until there is actually content to read from the socket. */
	n = read(new_sock_file_desc, buffer, 5);
	printf("Read from socket: %s\n", buffer);
	if (n < 0) {
		error("ERROR reading from socket");
		close(new_sock_file_desc);
		exit(1);
   }
   /* Read the file name */
   char temp[16];
   bzero(temp, 16);   
	bzero(fileName, LENGTH);	
	int i = 0;
	while( temp[0] != '\r' )
	{
	   if ( (n = read(new_sock_file_desc, temp, 1)) < 0 )
	      error("ERROR reading from socket");
		strcat(fileName, temp);
		i++;
   }
   fileName[i-1] = '\0';	
	/* Read the trailing \n\r\n and discard it. */
	read(new_sock_file_desc, temp, 3);
	size_t nbytes = 0;
	/* ******************************************************/
	/*  GET                                                 */
	/********************************************************/
	if ( strncmp(buffer, "GET", 3) == 0 )
	{
	   fileName[i-10] = '\0';
		printf("Client requests file: %s\n", fileName);
		FILE *fp;
		fp = fopen(fileName, "r");
		if (fp == NULL)
		{
		/* Respond back to Client that File cannot be found */
		   strcpy(buffer, "HTTP/1.1 404 Not Found\r\n\r\n");
	      n = send(new_sock_file_desc, buffer, strlen(buffer), 0);
	      if (n < 0)
		      error("ERROR writing to socket");
			error("ERROR opening file");
	   }
	   /* Find out the size of the file */
	   int size = 0;
		if (fp) 
		{
		   fseek(fp, 0L, SEEK_END);
		   size = ftell(fp);
		}
		/* rewind file pointer to start of file */
		fseek(fp, 0L, SEEK_SET);
	   /* Respond back to Client that File has been found */
		strcpy(buffer, "HTTP/1.1 200 OK\r\n\r\n");
	   n = send(new_sock_file_desc, buffer, strlen(buffer), 0);
	   if (n < 0)
		   error("ERROR writing to socket");		
		/* Send the file body. */
		while ( (n = fread(buffer, sizeof(char), LENGTH, fp)) != 0 )
		{
			if (send(new_sock_file_desc, buffer, n, 0) < 0)
				error("ERROR sending to socket");
			bzero(buffer, LENGTH);
		}
		printf("Done sending file\n");
		fclose(fp);	
	}
	/*************************************************/
	/* PUT CASE                                      */
	/*************************************************/
	else if ( strncmp(buffer, "PUT", 3) == 0 )
	{	
	   printf("File name: %s \n", fileName);
		/* Read the size of the file. */
		bzero(temp, sizeof(temp));
		bzero(buffer, LENGTH);
		while( temp[0] != '\r' )
	   {
	      if ( (n = read(new_sock_file_desc, temp, 1)) < 0 )
		      error("ERROR reading from socket");
		   strcat(buffer, temp);
      }
		bytesToRead = atoi(buffer);
		
		/* Read the trailing \n\r\n and discard it. */
	   read(new_sock_file_desc, temp, 3);
	   
		/* Open file for writing */
		FILE *fp = fopen(fileName, "w");
		if (fp == NULL)
			error("ERROR opening file");
		
		/* Read from socket and write to file */
		bzero(buffer, LENGTH);
		while ( bytesToRead > 0 && (n = recv(new_sock_file_desc, buffer, LENGTH, 0)) > 0 )
		{
			if ( (write_size = fwrite(buffer, sizeof(char), n, fp)) < nbytes )
				error("ERROR write failed on server");
			bytesToRead -= n;
			bzero(buffer, LENGTH);
		}	
		if (n < 0)
			error("ERROR recv failed");
			
	   printf("Done receiving file!\n");
		fclose(fp);
		/* Respond back to Client that File has been created */
		strcpy(buffer, "HTTP/1.1 00 OK File Created\r\n\r\n");
	   n = send(new_sock_file_desc, buffer, strlen(buffer), 0);
	   if (n < 0)
		   error("ERROR writing to socket");
	}
}
