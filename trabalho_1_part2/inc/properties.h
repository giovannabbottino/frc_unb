#ifndef PROPERTIES
#include <stdio.h> /* printf(), perror() */
#include <stdlib.h> 
#include <string.h>
#include <netinet/in.h> /* struct sockaddr_in */
#include <sys/socket.h> /* connect() send() bind() recv() */
#include <arpa/inet.h>  /* htons(), inet_addr() */
#include <sys/types.h> /* AF_INET, SOCK_STREAM pid_t */
#include <strings.h> /* bzero() */
#include <ctype.h> /* isdigit*/
#include <unistd.h>  /* fork() */

#define HOST "127.0.0.1"
#define PORT 5055

#endif