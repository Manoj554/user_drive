/*
 *
 *
 *File name : GetUserFile.c
 *
 *
 *Author : Team 4
 *
 *
Description : Used to receive the files from client to server during file upload. 
 *
 *
 *
 */

#ifndef __HEADER__
#include "../../server.h"
#endif

void get_user_file(int sockfd,char *net_buf)
{
    FILE *fp;
    int nBytes;
    char file_name[FILE_SIZE];
    printf("\n[+] Waiting for uploaded file name....\n");
    //clearBuf(net_buf);
    nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

    printf("[-] File Name Received: %s\n",net_buf);

    strcpy(file_name,net_buf);


    printf("********************File Content*******************\n");
    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);


        /*saving file at server side*/

        if(recv_file_save(net_buf,NET_BUF_SIZE,file_name))
        {

            break;
        }
    }
    printf("\n***************************************************\n");

}
