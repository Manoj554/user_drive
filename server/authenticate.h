#define USER_NOT_FOUND "user_not_found"
#define USER_FOUND "user_found"
#define AUTH_SUCCESS "Auth_success"
#define AUTH_FAILED "Auth_failed"

void user_authentication(int sockfd,char *net_buf,SA addr_con,int addrlen)
{
  printf("Authentication process start \n");
  int flag = 0;
  char buff[30], temp[30];
  char userdata[2][30];
  FILE *fp;

  memset(userdata, '\0', sizeof(userdata));

  fp = fopen("./server-files/userdb", "r+");

  strcpy(buff, (net_buf + strlen(AUTHENTICATE)));

  while(fscanf(fp, "%s", temp) != EOF)
  {
    if(flag == 1)
    {
      strcpy(userdata[1], temp);
      break;
    }

    if(strcmp(temp, buff) == 0)
    {
      strcpy(userdata[0], temp);
      flag = 1;
    }
  }
 
  printf("Userdata[0]: %s, Userdata[1]: %s \n", userdata[0], userdata[1]);

  if(strcmp(userdata[0], "\0") == 0)
  {
    strcpy(net_buf, USER_NOT_FOUND);
    printf("User authentication failed with : %s \n", net_buf);
    send(sockfd, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);
    clearBuf(net_buf);
  } 
  else
  {  
    strcpy(net_buf, USER_FOUND);
    printf("User password required to complete authentication !!!\n");
    send(sockfd, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);
    clearBuf(net_buf);
    recv(sockfd, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);

    printf("password received from client is : %s \n", net_buf);

    if(strcmp(net_buf, userdata[1]) == 0)
    {
      clearBuf(net_buf);
      strcpy(net_buf, AUTH_SUCCESS);
      send(sockfd, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);
      printf("Authention sucess !!! \n");
    }
    else
    {
      clearBuf(net_buf);
      strcpy(net_buf, AUTH_FAILED);
      send(sockfd, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);
      printf("Authention failed !!! \n");
    }
  }
  
  fclose(fp);
  printf("Authentication function terminates \n");
}
