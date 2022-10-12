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
#define END_CONNECTION "End_Connection"
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"

#define FILE_SIZE 100
#define IP_PROTOCOL 0
#define PORT_NO     5556
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define EXIT "exit"
#define IP_ADDRESS  "192.168.56.101"
#define nofile "File_Not_Found"

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
int recvFile_save(char *buf,int s,char *file_name)
{
    FILE *fp;
    int i;
    char ch;
    char file_error[] = "File_Not_Found";
    char base_address[FILE_SIZE] = "./users-drive-download-files/";
    strcat(base_address,file_name);
/*    if(strcmp(buf,file_error)==0)
    {
        return;
    }
*/
    fp = fopen(base_address,"wb");
    
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
            fputc(ch,fp);
            printf("%c",ch);
            //sleep(2);
        }
    }

    fclose(fp);
    return 0;
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
int file_found(char *buf,int s)
{
    char file_error[] = "File_Not_Found";
    char string[strlen(buf) - 1];
    int i = 0;
    for(i=0;i<strlen(buf)-1;i++)
    {
        string[i] = Cipher(buf[i]);
    }

    printf("String: %s\n",string);
    if(strcmp(string,file_error)==0)
    {
        return -1;
    }

   return 0;
}
void Download(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen,char *file_name)
{
    int nBytes;
    FILE *fp;
    clearBuf(net_buf);
    strcpy(net_buf,PUSH_DOWNLOAD_FILE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\nPlease Enter file name....\n");
    scanf("%s",net_buf);
    strcpy(file_name,net_buf);
    if(strcmp(net_buf,EXIT)==0)
    {
        return;
    }
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    printf("\n***********Data Received************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);


        /*saving file at client side*/
        if(file_found(net_buf,NET_BUF_SIZE)==-1)
        {
            break;
        }

        if(recvFile_save(net_buf,NET_BUF_SIZE,file_name))
        {
            break;
        }
    }
    printf("\n************************************\n"); 
}

void EndConnection(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
{
    int nBytes;
    strcpy(net_buf,END_CONNECTION);
    printf("Dissconnected...........\n");
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag); 
}
void ListAllDriveFiles(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
{
    int nBytes;
    clearBuf(net_buf);
    strcpy(net_buf,LIST_DIR);
    printf("Inside List Drive\n");
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n***********Data Received************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        /*saving file at client side*/
        //save_file(fp,net_buf,NET_BUF_SIZE,file_name);
        //
        //printf("Recieved Directory List %s\n",net_buf)
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
    
    // char array to store incoming and outgoing message
    char net_buf[NET_BUF_SIZE]; /* Used for Data Transfer*/
    char file_name[FILE_SIZE];/* Requested File Name */
    FILE *fp;
    socklen_t addrlen;// = sizeof(addr_con);
                      // Socket id
    int clientSocket, ret;

    // Client socket structure
    struct sockaddr_in cliAddr;

    struct sockaddr_in serverAddr;


    // Creating socket id
    clientSocket = socket(AF_INET,
            SOCK_STREAM, 0);

    if (clientSocket < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");

    // Initializing socket structure with NULL
    memset(&cliAddr, '\0', sizeof(cliAddr));


    // Assigning port number and IP address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);

    serverAddr.sin_addr.s_addr
        = inet_addr(IP_ADDRESS);

    // connect() to connect to the server
    ret = connect(clientSocket,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    if (ret < 0) {
        printf("Error in connection.\n");
        exit(1);
    }

    printf("Connected to Server.\n");
    while(1)
    {
        printf("Enter\n1. List All Downloaded Files\n2. List All Files on server\n3. Download\n4. Upload\n5. Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: ListAllDownloaded();
                    break;

            case 2: ListAllDriveFiles(clientSocket,net_buf,cliAddr,addrlen);
                    break;


            case 3: Download(clientSocket,net_buf,cliAddr,addrlen,file_name);
                    break;


            case 4: Upload();
                    break;

            case 5: EndConnection(clientSocket,net_buf,cliAddr,addrlen);
                    return 0;

            default: continue;

        }

    }
    return 0;

}
