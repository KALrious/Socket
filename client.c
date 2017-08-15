//
//  client.c
//  
//
//  Created by jean gautier on 15/05/2016.
//
//

#include "client.h"
#define max 9


char **images[max][max];

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

static int init_connection(const char *address)
{
    struct sockaddr addrConnect;
    int nPort = 5000;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   
    SOCKADDR_IN sin = { 0 };
    struct hostent *hostinfo;
    
     
    
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    
    hostinfo = gethostbyname(address);
    if (hostinfo == NULL)
    {
        fprintf (stderr, "Unknown host %s.\n", address);
        exit(EXIT_FAILURE);
    }
    
    memset(&sin,'0',sizeof(sin));
    
    //sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    
    if(inet_pton(AF_INET, address, &sin.sin_addr)<=0)
    {
        perror("IP");
        exit(errno);
    }
    
    addrConnect = TcpFormatAdress( address, (u_short)nPort );
    
    
    
        
    if(connect(sock, &addrConnect, sizeof(addrConnect)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }
   
    
    return sock;
}

static void end_connection(int sock)
{
    closesocket(sock);
}

void obstacle (char *tab)
{
    
    int i=0,j=0,k=0;
    char buff[100]="";
    char chaine[100];
    char * pszHost = "127.0.0.1";
    /*envoie l'images à l'aide d'un socket réseau
     
     */
    for(i=0;i<10 ; i++)
    {
        sprintf(chaine, "%d ", tab[i]);
        strcat(buff,chaine);

        for(j=i+1;j<10;j++)
        {
            
            if (tab[j] == tab[i])
            {
                k=1;
            }
        }
        
    }
    
        
    if(k=1)
    {
        //memset(tab,'0',sizeof(tab));
        SOCKET sock = init_connection(pszHost);
    
    
            if(send(sock, buff, strlen(buff), 0) < 0)
            {
                perror("send()");
                exit(errno);
     
            }
    
        end_connection(sock);
    }
    sleep(5);
    
}

int main()
{
    char *tab = NULL;
    int i=0,k=0,j=0;
    
    tab = malloc(10*sizeof(char));
    if (tab == NULL) // Si l'allocation a échoué
    {
        exit(0); // On arrête immédiatement le programme
    }
     
   do
    {
        get_image(tab);
        
        for(j=0;j<max;j++)
            images[i][j]=tab[j];

        k=0;
        for(j=0;j<max;j++)
            images[i][j]=tab[j];
        tab = process_image(tab);
        
        obstacle(tab);
        i++;
    }while(i<max-1);
    free(tab);
}