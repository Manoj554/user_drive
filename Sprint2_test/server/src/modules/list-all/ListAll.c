#include "../../server.h"
void ListAll(int sockfd,char *net_buf,int addrlen)
{
    printf("LIST_DIR command received %s \n",net_buf);
    FILE *fp1,*fp2;
    DIR *d;
    struct dirent *dir;
    char string[NET_BUF_SIZE];
    d = opendir("./shared-storage/");
    fp1 = fopen("./server-files/Directory_Index.txt","wb");
    if (d)
    {
        printf("*********************Listed All Files********************\n");
        while ((dir = readdir(d)) != NULL)
        {
            if(fp1 ==NULL)
            {
                printf("\nLIST_DIR command failed!!\n");
            }
            else
            {
                strcat(string,dir->d_name);
                strcat(string,EOL);
            }

           //printf("%s\n", dir->d_name);
        }

        string[strlen(string) - 1] = EOF;
        printf("String Data : %s\n",string);
        fwrite(string,sizeof(char),sizeof(string),fp1);
        closedir(d);

        fclose(fp1);
        printf("*********************************************************\n");
    }
    clearBuf(net_buf);
    fp2 = fopen("./server-files/Directory_Index.txt","rb");
    if(fp2 ==NULL)
    {
        printf("\nFile open failed!!\n");
    }
    else
    {
        printf("\nFile Open Successfull!!\n");
    }
    while(1)
    {
        if(sendFile(fp2,string,NET_BUF_SIZE)){
            send(sockfd,string,NET_BUF_SIZE,sendrecvflag);
            clearBuf(string);

            break;
        }
        if(fp2!=NULL)
        {
            fclose(fp2);
        }
    }

}
