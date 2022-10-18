/*
*
*
*File name : ListAllDriveFiles.c
*
*
*Author : Team 4
*
*
Description : Used to display the files present on the server by sending command and receiving data 
*
*
*
*/

#ifndef __HEADER__
#include "../../client.h"
#endif

void list_all_drive_files(int sockfd,char *net_buf)
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
        if(recv_file(net_buf,NET_BUF_SIZE))
        {
            break;
        }
    }
    
    printf("\n***********************************************\n"); 
}
