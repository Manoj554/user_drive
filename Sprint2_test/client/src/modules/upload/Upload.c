#include "../../client.h"
void Upload(int sockfd,char *net_buf,int addrlen)
{
    int nBytes;
    FILE *fp;
    char *file_name;
    clearBuf(net_buf);
    strcpy(net_buf,PUSH_UPLOAD_FILE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\nPlease Enter file name to upload....\n");
    scanf("%s",net_buf);
    //strcpy(file_name,net_buf);
    if(strcmp(net_buf,EXIT)==0)
    {
        return;
    }
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    printf("%s\n",net_buf);
    char base_address[100] = "./users-drive-download-files/";
    //relative_address = net_buf;
    strcat(base_address,net_buf);
    //printf("Concatanated address : %s\n",base_address);
    fp = fopen(base_address,"rb");

    if(fp == NULL)
    {
        printf("\nFile open failed\n");
    }
    else
    {
        printf("\nFile open successfully\n");
    }

    //printf("\n***********Downloaded Content************\n");

    while(1)
    {
        printf("Inside Loop\n");
        //count++;
        if(sendFile(fp,net_buf,NET_BUF_SIZE)){
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