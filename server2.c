#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <dirent.h>

/*Commands*/
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"

#define IP_PROTOCOL 0
#define PORT_NO     5000
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define FILE_NAME_SIZE 100
#define nofile "File Not Found!"
#define EOL "\n"
void clearBuf(char *b)
{
    int i;
    for(i = 0;i<NET_BUF_SIZE;i++)
    {
        b[i] = '\0';
    }
}
char Cipher(char ch)
{
    return ch ^ cipherKey; //Encryption using XOR
}
int sendFile(FILE *fp,char *buf,int s)
{
    int i, len;
    if(fp==NULL)
    {
        strcpy(buf,nofile);
        len = strlen(nofile);
        buf[len] = EOF;
        for(i = 0;i<=len;i++)
        {
            buf[i] = Cipher(buf[i]);
        }
        return 1;
    }
    char ch,ch2;
    for(i =0;i<s;i++)
    {
        ch = fgetc(fp);
        ch2 = Cipher(ch);
        buf[i] = ch2;
        if(ch == EOF)
            return 1;
    }

    return 0;
}
void ListAll(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
{
    printf("LIST_DIR command received %s \n",net_buf);
    FILE *fp;
    DIR *d;
    struct dirent *dir;
    char string[NET_BUF_SIZE];
    d = opendir("./shared-storage/");
    fp = fopen("./server-files/Directory_Index.txt","wb");
    if (d)
    {
        printf("*********************Listed All Files********************\n");
        while ((dir = readdir(d)) != NULL)
        {
            if(fp ==NULL)
            {
                printf("\nLIST_DIR command failed!!\n");
            }
            else
            {
                strcat(string,dir->d_name);
                strcat(string,EOL);
            }

            printf("%s\n", dir->d_name);
        }
        
        printf("String Data : %s\n",string);
        string[strlen(string) - 1] = '\0';
        fwrite(string,sizeof(char),sizeof(string),fp);
        closedir(d);

        fclose(fp);
        printf("*********************************************************\n");
    }

    fp = fopen("./server-files/Directory_Index.txt","rb");
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
        if(sendFile(fp,net_buf,NET_BUF_SIZE)){
            sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
            clearBuf(net_buf);

            break;
        }
        if(fp!=NULL)
        {
            fclose(fp);
        }
    }

}
void PushDownloadFile(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
{
    FILE *fp;
    int nBytes;
    while(1)
    {
        printf("\nWaiting for file name....\n");
        clearBuf(net_buf);
        nBytes = recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,&addrlen);

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
                sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
                clearBuf(net_buf);

                break;
            }
            if(fp!=NULL)
            {
                fclose(fp);
            }
        }

    }
}
int main()
{
    int sockfd,nBytes;
    struct sockaddr_in addr_con;
    int addrlen = sizeof(addr_con);
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = INADDR_ANY;
    char net_buf[NET_BUF_SIZE];
    FILE *fp;

    /* Create server socket */
    sockfd = socket(AF_INET, SOCK_DGRAM,IP_PROTOCOL);
    if (sockfd == -1)
    {
        fprintf(stderr, "Error creating socket --> %s", strerror(errno));

        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nFile Descriptor %d received\n",sockfd);
    }

    /* Bind */
    if ((bind(sockfd, (struct sockaddr *)&addr_con, sizeof(addr_con))) == -1)
    {
        fprintf(stderr, "Error on bind --> %s", strerror(errno));

        exit(EXIT_FAILURE);
    }

    /*Receiving command*/
    while(1)
    {
    nBytes = recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,&addrlen);


        if(strcmp(net_buf,LIST_DIR)==0)
        {
            ListAll(sockfd,net_buf,addr_con,addrlen);
        }else if(strcmp(net_buf,PUSH_DOWNLOAD_FILE)==0)
        {
            PushDownloadFile(sockfd,net_buf,addr_con,addrlen);
        }

    }
    return 0;
}
