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

#define FILE_SIZE 100
#define IP_PROTOCOL 0
#define PORT_NO     5000
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define EXIT "exit"
#define IP_ADDRESS  "192.168.56.101"


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
int recvFile(char *buf,int s)
{
    int i;
    char ch;
    for(i = 0;i<s;i++)
    {
        ch = buf[i];
        ch = Cipher(ch);
        if(ch == EOF)
        {
            return 1;
        }
        else
        {
            printf("%c",ch);
            //sleep(2);
        }
    }
    return 0;
}
void save_file(FILE *fp,char *buf,int s,char *file_name)
{
    char *nofile = "File Not Found!";
    char base_address[FILE_SIZE] = "./users-drive-download-files/";
    strcat(base_address,file_name);
    fp = fopen(base_address,"wb");
    char string[strlen(buf) - 1];
    int i = 0;
    for(i=0;i<strlen(buf);i++)
        string[i] = Cipher(buf[i]);

    string[i] = '\0';
    printf("\nFile Name Received: %s\n",file_name);

    if(fp ==NULL)
    {
        printf("\nDownload failed!!\n");
    }else if(strcmp(string,nofile)==0)//Solve This
    {
        printf("Entered Here \n");
        fclose(fp);
        return;
    }
    else
    {
        fwrite(string,sizeof(char),sizeof(string),fp);
        printf("\nDownload  Successfull!!\n");
    }
    fclose(fp);

}
void Download(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen,char *file_name)
{
    int nBytes;
    FILE *fp;
    strcpy(net_buf,PUSH_DOWNLOAD_FILE);
    sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
    while(1)
    {

        printf("\nPlease Enter file name....\n");
        scanf("%s",net_buf);
        strcpy(file_name,net_buf);
        if(strcmp(net_buf,EXIT)==0)
        {
            return;
        }
        sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
        printf("\n***********Data Received************\n");

        while(1)
        {
            clearBuf(net_buf);
            nBytes = recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,&addrlen);

            /*saving file at client side*/
            save_file(fp,net_buf,NET_BUF_SIZE,file_name);

            if(recvFile(net_buf,NET_BUF_SIZE))
            {
                break;
            }
        }
        printf("\n************************************\n"); 
    }
}

void ListAllDriveFiles(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
{
    int nBytes;
    strcpy(net_buf,LIST_DIR);
    sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
    printf("\n***********Data Received************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,&addrlen);

        /*saving file at client side*/
        //save_file(fp,net_buf,NET_BUF_SIZE,file_name);

        if(recvFile(net_buf,NET_BUF_SIZE))
        {
            break;
        }
    }
    printf("\n************************************\n"); 
}
void ListAllDownloaded()
{
    DIR *d;
    struct dirent *dir;
    d = opendir("./users-drive-download-files/");
    if (d)
    {

    printf("\n***********Data Received************\n");
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    printf("\n************************************\n");
    }
}

void Upload(){}
int main()
{
    int choice;
    int sockfd,nBytes;
    struct sockaddr_in addr_con;
    int addrlen = sizeof(addr_con);
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    char net_buf[NET_BUF_SIZE]; /* Used for Data Transfer*/
    char file_name[FILE_SIZE];/* Requested File Name */
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



    if (sockfd == -1)
    {
        fprintf(stderr, "Error on bind --> %s", strerror(errno));

        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nFile Descriptor %d received\n",sockfd);
    }


    while(1)
    {
        printf("Enter\n1. List All Downloaded Files\n2. List All Files on server\n3. Download\n4. Upload\n5. Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: ListAllDownloaded();
                    break;

            case 2: ListAllDriveFiles(sockfd,net_buf,addr_con,addrlen);
                    break;


            case 3: Download(sockfd,net_buf,addr_con,addrlen,file_name);
                    break;


            case 4: Upload();
                    break;

            case 5: return 0;

            default: continue;

        }

    }
    return 0;

}
