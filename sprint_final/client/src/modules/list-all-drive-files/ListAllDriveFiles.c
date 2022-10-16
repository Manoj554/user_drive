#include "../../client.h"

void ListAllDriveFiles(int sockfd,char *net_buf,int addrlen)
{
    printf("[+] All files in server \n");

    int nBytes;
    clearBuf(net_buf);
    strcpy(net_buf,LIST_DIR);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n************** User Drive Files ***************\n");
  
    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        if(recvFile(net_buf,NET_BUF_SIZE))
        {
            break;
        }
    }
    
    printf("\n***********************************************\n"); 
}
