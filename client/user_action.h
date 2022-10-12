
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
    char file_error[] = "File_Not_Found";
    char base_address[FILE_SIZE] = "./users-drive-download-files/";
    strcat(base_address,file_name);
    char string[strlen(buf) - 1];
    int i = 0;
    for(i=0;i<strlen(buf)-1;i++)
        string[i] = Cipher(buf[i]);
    if(strcmp(string,file_error)==0)
    {
        return;
    }

    fp = fopen(base_address,"wb");
    string[i] = '\0';

    printf("\nFile Name Received: %s\n",file_name);

    printf("File Error: %s SIZE OF STRING: %ld STRLEN OF BUF %ld STRLEN of STRING %ld STRCMP %d STRING %s\n\n\n",file_error,sizeof(string),strlen(buf),strlen(string),strcmp(string,file_error),string);
    if(fp ==NULL)
    {
        printf("\nDownload failed!!\n");
    }
    else
    {
        fwrite(string,sizeof(char),sizeof(string),fp);
        printf("\nDownload  Successfull!!\n");
    }
    fclose(fp);

}
void Download(int sockfd,char *net_buf,SA addr_con,int addrlen,char *file_name)
{
    int nBytes;
    FILE *fp;
    strcpy(net_buf,PUSH_DOWNLOAD_FILE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

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
            save_file(fp,net_buf,NET_BUF_SIZE,file_name);

            if(recvFile(net_buf,NET_BUF_SIZE))
            {
                break;
            }
        }
        printf("\n************************************\n"); 
}

void EndConnection(int sockfd,char *net_buf, SA addr_con,int addrlen)
{
    int nBytes;
    strcpy(net_buf,END_CONNECTION);
    printf("Dissconnected...........\n");
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag); 
}
void ListAllDriveFiles(int sockfd,char *net_buf, SA addr_con,int addrlen)
{
    int nBytes;
    strcpy(net_buf,LIST_DIR);
    printf("Inside List Drive\n");
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    printf("\n***********Data Received************\n");

    while(1)
    {
        clearBuf(net_buf);
        nBytes = recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

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
