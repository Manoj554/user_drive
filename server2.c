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
#include <pthread.h>

/*Commands*/
#define END_CONNECTION "End_Connection"
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"

#define IP_ADDRESS "192.168.56.101"
#define IP_PROTOCOL 0
#define PORT_NO     5556
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define FILE_NAME_SIZE 100
#define nofile "File_Not_Found"
#define EOL "\n"

typedef struct connection_data
{
    int clientSocket;
    char *net_buf;
    struct sockaddr_in serverAddr;
    int addr_size;

}connec_data_t;

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
void PushDownloadFile(int sockfd,char *net_buf,struct sockaddr_in addr_con,int addrlen)
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
void *HandleConnection(void *new_socket_details)
{
    connec_data_t *parcel_ptr = (connec_data_t *) new_socket_details;

    int clientSocket;
    char *net_buf;
    struct sockaddr_in serverAddr;
    int addr_size;

    clientSocket = parcel_ptr->clientSocket;
    net_buf = parcel_ptr->net_buf ;
    serverAddr = parcel_ptr->serverAddr;
    addr_size =  parcel_ptr->addr_size;

    /*Receiving command*/
        while(1)
        {
            recv(clientSocket,net_buf,NET_BUF_SIZE,sendrecvflag);


            if(strcmp(net_buf,LIST_DIR)==0)
            {
                ListAll(clientSocket,net_buf,serverAddr,addr_size);
            }else if(strcmp(net_buf,PUSH_DOWNLOAD_FILE)==0)
            {
                PushDownloadFile(clientSocket,net_buf,serverAddr,addr_size);
            }else if(strcmp(net_buf,END_CONNECTION)==0)
            {
                close(clientSocket);
                break;
            }

        }
        return NULL;
}
int main()
{
    char net_buf[NET_BUF_SIZE];
    FILE *fp;
    // Server socket id
    int sockfd, ret;

    // Server socket address structures
    struct sockaddr_in serverAddr;

    // Client socket id
    int clientSocket;

    // Client socket address structures
    struct sockaddr_in cliAddr;

    // Stores byte size of server socket address
    socklen_t addr_size;

    // Child process id
    pid_t childpid;

    // Creates a TCP socket id from IPV4 family
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Error handling if socket id is not valid
    if (sockfd < 0) {
        printf("Error in connection.\n");
        exit(1);
    }

    printf("Server Socket is created.\n");

    // Initializing address structure with NULL
    memset(&serverAddr, '\0',
            sizeof(serverAddr));

    // Assign port number and IP address
    // to the socket created
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);

    // 127.0.0.1 is a loopback address
    serverAddr.sin_addr.s_addr
        = inet_addr(IP_ADDRESS);

    // Binding the socket id with
    // the socket structure
    ret = bind(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Error handling
    if (ret < 0) {
        printf("Error in binding.\n");
        exit(1);
    }

    // Listening for connections (upto 10)
    if (listen(sockfd, 10) == 0) {
        printf("Listening...\n\n");
    }

    int cnt = 0;


    while(1)
    {
        clientSocket = accept(sockfd, (struct sockaddr*)&cliAddr,&addr_size);

        // Error handling
        if (clientSocket < 0) {
            exit(1);
        }

        // Displaying information of
        // connected client
        printf("Connection accepted from %s:%d\n",
                inet_ntoa(cliAddr.sin_addr),
                ntohs(cliAddr.sin_port));

        // Print number of clients
        // connected till now
        printf("Clients connected: %d\n\n",
                ++cnt);

        pthread_t t;
        //int *pclient = malloc(sizeof(int));
        //*pclient = clientSocket; 

        connec_data_t *parcel_ptr;
        connec_data_t parcel;
        parcel.clientSocket = clientSocket;
        parcel.net_buf = net_buf;
        parcel.serverAddr = serverAddr;
        parcel.addr_size = addr_size;

        parcel_ptr = &parcel;

        //HandleConnection(parcel_ptr);
        
        pthread_create(&t,NULL,HandleConnection,parcel_ptr);
       
    }
    return 0;
}
