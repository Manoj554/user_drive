/*
*
*
*File name : DeleteFile.c
*
*
*Author : Team 4
*
*
Description : Used to delete the files present on the server. 
*
*
*
*/

#include "../../server.h"
void delete_file(int sockfd,char *net_buf)
{
    	char file_name[FILE_SIZE];
        printf("\n[+] Waiting for file name to be deleted....\n");

        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

       printf("[+] File Name Received: %s\n",net_buf);

       strcpy(file_name,net_buf);

       clearBuf(net_buf);
       char base_address[FILE_SIZE] = "./shared-storage/";
       strcat(base_address,file_name);

       if(remove(base_address) == 0)
       {
           strcpy(net_buf,CMD_SUCCESS);
       }
       else
       {
           strcpy(net_buf,CMD_NOT_SUCCESS);
       }
       send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
       clearBuf(net_buf);
       
}
