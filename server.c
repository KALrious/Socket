//
//  server.c
//  
//
//  Created by jean gautier on 15/05/2016.
//
//

#include "server.h"



static struct sockaddr TcpFormatAdress( char * host, u_short port )
{
    struct sockaddr_in addr;
    struct sockaddr addrRet;
    struct hostent *lphost ;
    u_long IP;
    
    
    memset((char*)&addr, 0, sizeof(addr));
    /*	Soit on fournit une adresse IP, soit on fournit un nom	*/
    if ((IP = inet_addr(host)) == (u_long)INADDR_NONE)
    {
        if ((lphost  = gethostbyname(host))==NULL)
        {
            memset( (char * )&addrRet, 0, sizeof(addrRet) );
            return  addrRet;
        }
        addr.sin_family = lphost->h_addrtype;
#ifdef _WIN16 /* A définir dans le projet WIN16	*/
        _fmemcpy (&addr.sin_addr, lphost->h_addr, lphost->h_length);
#else /*	WIN32, UNIX*/
        memcpy (&addr.sin_addr, lphost->h_addr, lphost->h_length);
#endif
    }
    else
    {
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = IP;
    }
    
    /*  Port destination    */
    addr.sin_port = htons((u_short)port );
    
    memcpy( (char *)&addrRet, (char *)&addr, sizeof(addrRet) );
    return addrRet;
}

static int read_client(SOCKET sock, int *buffer)
{
    int n = 0;
    int i=0,j=0;
    
    if((n = recv(sock, buffer,sizeof(buffer), 0)) < 0)
    {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }
    
    
    
    
        for(j=0;j<10;j++)
        {
            printf(" %d\t",buffer[i]);
        }
        printf("\naffichage collision \n");
    return n;
}


int main(void)
{
    
    int nPort;
    int ret = 1,n=0,j=0,i=0;
    int connectfd=0;
    SOCKADDR_IN sin;
    char c;
    SOCKET sock;
    struct sockaddr addrConnect;
    char *address;
    char *buff;
    nPort = PORT;
    address = "127.0.0.1";
    
    buff = malloc(10*sizeof(char));
    if (buff == NULL) // Si l'allocation a échoué
    {
        exit(0); // On arrête immédiatement le programme
    }
    
    /*création socket*/
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
   
    
    //accept les connections entrantes
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr =htonl (address);
    sin.sin_port = htons(PORT);
    
     addrConnect = TcpFormatAdress( address, (u_short)nPort );
    
    //bind adresse au socket
    if(bind(sock,(SOCKADDR *) &addrConnect, sizeof(addrConnect)) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }
    //connection entrante
    if(listen(sock, 100) == SOCKET_ERROR)
        {
            perror("listen()");
            exit(errno);
        }
   
      //accpete connection
      if(  (connectfd = accept(sock,(struct sockaddr *)NULL,NULL)) <0)
      {
          perror("accept");
          exit(errno);
      }
    while(1)
    {
        do{
             if((n = recv(connectfd, buff,sizeof(buff), 0)) < 0)
            {
                perror("recv()");
                /* if recv error we disonnect the client */
                n = -1;
            }
            if(n>=0)
            printf( "%s", buff );
            
            ret = n;
            sleep(5);
        }while(ret>0);
        printf("\n");
    }
    free(buff);
    
}