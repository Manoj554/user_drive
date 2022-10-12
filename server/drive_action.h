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

int sendFile(FILE *fp, char *buf, int s)
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


void ListAll(int sockfd, char *net_buf, SA addr_con, int addrlen)
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
      send(sockfd,net_buf,NET_BUF_SIZE, SEND_RECEIVE_FLAG);
      clearBuf(net_buf);

      break;
    }
    if(fp!=NULL)
    {
      fclose(fp);
    }
  }
}


void PushDownloadFile(int sockfd, char *net_buf, SA  addr_con,int addrlen)
{
  FILE *fp;
  int nBytes;
  printf("\nWaiting for file name....\n");
  clearBuf(net_buf);
  nBytes = recv(sockfd,net_buf,NET_BUF_SIZE, SEND_RECEIVE_FLAG);

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
      send(sockfd,net_buf,NET_BUF_SIZE, SEND_RECEIVE_FLAG);
      clearBuf(net_buf);

      break;
    }
    if(fp!=NULL)
    {
      fclose(fp);
    }
  }
}
