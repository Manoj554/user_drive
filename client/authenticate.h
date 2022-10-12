#define USER_NOT_FOUND "user_not_found"
#define USER_FOUND "user_found"
#define AUTH_SUCCESS "Auth_success"
#define AUTH_FAILED "Auth_failed"


int user_authentication(int sockfd,char *net_buf, SA addr_con,int addrlen)
{
  int nBytes, n = 0;
  char buff[20];

  printf("Enter username :- ");
  scanf(" %[^\n]%*c", buff);

  strcpy(net_buf, AUTHENTICATE);
  strcat(net_buf, buff);

  send(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag);
  clearBuf(net_buf);
  recv(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag);

  printf("Response from server:  %s \n", net_buf);

  if(strcmp(net_buf, USER_NOT_FOUND) == 0)
  {
    printf("User not found !!! \n");
  }
  else
  {
    printf("password for %s :- ", buff);
    memset(buff, '\0', sizeof(buff));
    scanf(" %[^\n]%*c", buff);

    strcpy(net_buf, buff);

    send(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag);
    clearBuf(net_buf);
    recv(sockfd, net_buf, NET_BUF_SIZE, sendrecvflag);
    
    printf("Password Status : %s \n", net_buf);

    if(strcmp(net_buf, AUTH_SUCCESS) == 0)
    {
      return 1;
    }
    else
      printf("Authentication failed !!! \n");
  }

  printf("Auth Process terminate \n");
  return 0;
}
