/*
*
*
*File name : Download.c
*
*
*Author : Team 4
*
*
Description : Used to download the files from server shared storage
*
*
*
*/

#include "../../client.h"

void download(int sockfd,char *net_buf,char *file_name)
{
    int nBytes;
    clearBuf(net_buf);
    strcpy(net_buf,PUSH_DOWNLOAD_FILE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n[+] Please Enter file name....\n");
    scanf("%s",net_buf);
    strcpy(file_name,net_buf);
    if(strcmp(net_buf,EXIT)==0)
    {
        return;
    }
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

    printf("\n************* Downloaded Content *************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);


        /*saving file at client side*/
        if(file_found(net_buf,NET_BUF_SIZE)==-1)
        {
            break;
        }

        if(save_file(net_buf,NET_BUF_SIZE,file_name))
        {
            break;
        }
    }
    printf("\n**********************************************\n"); 
}
