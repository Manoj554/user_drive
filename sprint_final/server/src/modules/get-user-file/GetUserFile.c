#include "../../server.h"
void GetUserFile(int sockfd,char *net_buf,int addrlen)
{
    FILE *fp;
    int nBytes;
    char file_name[FILE_SIZE];
        printf("\n[+] Waiting for uploaded file name....\n");
        //clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

       printf("[-] File Name Received: %s\n",net_buf);

       strcpy(file_name,net_buf);


       //printf("File Received: %s\n",net_buf);

       printf("********************File Content*******************\n");
       while(1)
       {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);


        /*saving file at client side*/
        /*if(file_found(net_buf,NET_BUF_SIZE)==-1)
        {
            break;
        }*/

        if(recvFile_save(net_buf,NET_BUF_SIZE,file_name))
        {

            break;
        }
    }
    printf("\n***************************************************\n");

}
