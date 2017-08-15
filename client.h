//
//  client.h
//  
//
//  Created by jean gautier on 15/05/2016.
//
//

#ifndef client_h
#define client_h

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include "process.h"
#include "acquire.h"


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct hosten HOSTEN;
#define PORT	 5000
#define ADRESSE 2a01:cb00:3d0:2f00:54b3:4816:9e85:b86d


static int init_connection(const char *address);
static void end_connection(int sock);
void obstacle (char *tab);


#endif /* client_h */
