#include "../../server.h"
void DeleteFile(int sockfd,char *net_buf,int addrlen)
{
    char file_name[FILE_SIZE];
        printf("\nWaiting for file name to be deleted....\n");
        //clearBuf(net_buf);
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

       printf("File Name Received: %s\n",net_buf);

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
       //printf("File Received: %s\n",net_buf);
}
