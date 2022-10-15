#include "../../server.h"
void PushDownloadFile(int sockfd,char *net_buf,int addrlen)
{
    FILE *fp;
    int nBytes;
        printf("\nWaiting for file name....\n");
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        char base_address[100] = "./shared-storage/";
        //relative_address = net_buf;
        strcat(base_address,net_buf);
        //printf("Concatanated address : %s\n",base_address);
        fp = fopen(base_address,"r");
        printf("\nFile Name Received: %s\n",net_buf);

        if(fp ==NULL)
        {
            printf("\nFile open failed!!\n");
        }
        else
        {
            printf("\nFile Open Successfull!!\n");
        }

        while(1)
        {
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