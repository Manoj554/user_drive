/*
*
*
*File name : PushDownloadFiles.c
*
*
*Author : Team 4
*
*
Description : Used to send the files present on the server to clients on request.
*
*
*
*/

#include "../../server.h"
void push_download_file(int sockfd,char *net_buf)
{
    FILE *fp;
    int nBytes;
        printf("\n[+] Waiting for file name....\n");
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        char base_address[100] = "./shared-storage/";
        //relative_address = net_buf;
        strcat(base_address,net_buf);
        //printf("Concatanated address : %s\n",base_address);
        fp = fopen(base_address,"r");
        printf("\n[+] File Name Received: %s\n",net_buf);

        if(fp ==NULL)
        {
            printf("\n[failed] File open failed!!\n");
        }
        else
        {
            printf("\n[ok] File Open Successfull!!\n");
        }

        while(1)
        {
            //count++;
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
