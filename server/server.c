#include "server.h"
#include "drive_action.h"
#include "authenticate.h"

typedef struct connection_data
{
  int clientSocket;
  char *net_buf;
  SA serverAddr;
  int addr_size;

}conn_data_t;

void *HandleConnection(void *);


int main()
{
  char net_buf[NET_BUF_SIZE];

  //Socket ids for server and client
  int sockfd, connfd;
  int ret, clientNo = 0;

  //Socket address structures
  SA serverAddr, cliAddr;

  // Stores byte size of server socket address
  socklen_t addr_size;

  // Child process id
  pid_t childpid;

  // Creates a TCP socket id from IPV4 family
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Error handling if socket id is not valid
  if (sockfd < 0) 
  {
    perror("Connectin Error: ");
    exit(EXIT_FAILURE);
  }

  printf("Server Socket is created.\n");

  // Initializing address structure with NULL
  memset(&serverAddr, '\0', sizeof(serverAddr));

  // Assign port number and IP address to the socket created
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT_NO);
  serverAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS); // 127.0.0.1 is a loopback address


  // Binding the socket id with
  // the socket structure
  ret = bind(sockfd, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));

  // Error handling
  if (ret < 0) 
  {
    printf("Error in binding.\n");
    exit(EXIT_FAILURE);
  }

  // Listening for connections (upto 10)
  if (listen(sockfd, 10) == 0) 
  {
    printf("Server is Listening...\n\n");
  }

  while(1)
  {
    connfd = accept(sockfd, (struct sockaddr *) &cliAddr, &addr_size);

    // Error handling
    if (connfd < 0) 
    {
      exit(EXIT_FAILURE);
    }

    // Displaying information of connected client
    printf("Connection accepted from %s: %d\n", inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    // Print number of clients connected till now
    printf("Client No: %d\n\n", ++clientNo);

    pthread_t t;

    conn_data_t parcel;
    parcel.clientSocket = connfd;
    parcel.net_buf = net_buf;
    parcel.serverAddr = serverAddr;
    parcel.addr_size = addr_size;

    pthread_create(&t, NULL, HandleConnection, &parcel);

  }


  return EXIT_SUCCESS;
}

void *HandleConnection(void *new_socket_details)
{
  conn_data_t *parcel_ptr = (conn_data_t *) new_socket_details;

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
    recv(clientSocket, net_buf, NET_BUF_SIZE, SEND_RECEIVE_FLAG);
    
    if(strncmp(net_buf, AUTHENTICATE, (int) strlen(AUTHENTICATE)) == 0)
    {
      user_authentication(clientSocket, net_buf, serverAddr, addr_size);
    }
    else if(strcmp(net_buf, LIST_DIR) == 0)
    {
      ListAll(clientSocket, net_buf, serverAddr, addr_size);
    }
    else if(strcmp(net_buf, PUSH_DOWNLOAD_FILE) == 0)
    {
      PushDownloadFile(clientSocket, net_buf, serverAddr, addr_size);
    }
    else if(strcmp(net_buf, END_CONNECTION)==0)
    {
      close(clientSocket);
      break;
    }

  }

  return NULL;
}
