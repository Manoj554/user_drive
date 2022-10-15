#include "../../client.h"
void ListAllDriveFiles(int sockfd,char *net_buf,int addrlen)
{
    int nBytes;
    clearBuf(net_buf);
    strcpy(net_buf,LIST_DIR);
    printf("Inside List Drive\n");
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n***********************User Drive Files*************************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        /*saving file at client side*/
        //save_file(fp,net_buf,NET_BUF_SIZE,file_name);
        //
        //printf("Recieved Directory List %s\n",net_buf)
        if(recvFile(net_buf,NET_BUF_SIZE))
        {
            break;
        }
    }
    printf("\n*****************************************************************\n"); 
}