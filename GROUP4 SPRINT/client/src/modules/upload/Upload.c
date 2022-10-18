/*
*
*
*File name : Upload.c
*
*
*Author : Team 4
*
*
Description : Upload a particular file from local storage to the server. 
*
*
*
*/

#ifndef __HEADER__
#include "../../client.h"
#endif

void upload(int sockfd,char *net_buf)
{
    int nBytes;
    FILE *fp;
    char *file_name;
    clearBuf(net_buf);
    strcpy(net_buf,PUSH_UPLOAD_FILE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n[+] Please enter file name to upload....\n");
    scanf("%s",net_buf);

    if(strcmp(net_buf,EXIT)==0)
    {
        printf("[-] You can't use %s as file name \n", EXIT);
        return;
    }

    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    //printf("%s\n",net_buf);

    char base_address[100] = "./users-drive-download-files/";
    strcat(base_address,net_buf);
    fp = fopen(base_address,"rb");

    if(fp == NULL)
    {
        printf("\n[failed] File open failed\n");
    }
    else
    {
        printf("\n[ok] File open successfully\n");
    }

    //printf("\n***********Downloaded Content************\n");

    while(1)
    {
        if(send_file(fp,net_buf,NET_BUF_SIZE)){
            send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
            clearBuf(net_buf);

            break;
        }
        if(fp!=NULL)
        {
            fclose(fp);
        }
    }

}
