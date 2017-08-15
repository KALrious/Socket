//
//  server.h
//  
//
//  Created by jean gautier on 15/05/2016.
//
//

#ifndef server_h
#define server_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct hosten HOSTEN;
#define PORT	 5000
#define adresse 2a01:cb00:3d0:2f00:54b3:4816:9e85:b86d

static int read_client(SOCKET sock, int *buffer);


#endif /* server_h */
