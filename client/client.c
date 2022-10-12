#include "client.h"
#include "user_action.h"
#include "authenticate.h"

int main()
{

  // Client socket structure
  int choice, clientSocket, ret;
  int auth = 0;
  SA cliAddr, serverAddr;
  socklen_t addrlen;

  // char array to store incoming and outgoing message
  char net_buf[NET_BUF_SIZE];  /* Used for Data Transfer*/
  char file_name[FILE_SIZE];   /* Requested File Name */
  FILE *fp;                    /*File Pointer*/
  

  // Creating socket id
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (clientSocket < 0) 
  {
    printf("Error in connection.\n");
    exit(EXIT_FAILURE);
  }

  printf("Client Socket is created.\n");

  // Initializing socket structure with NULL
  memset(&cliAddr, '\0', sizeof(cliAddr));


  // Assigning port number and IP address
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT_NO);
  serverAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

  // connect() to connect to the server
  ret = connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

  if (ret < 0) 
  {
    printf("Error in connection.\n");
    exit(EXIT_FAILURE);
  }

  printf("Successfully Connected to Server.\n");

  while(1)
  {
    if(user_authentication(clientSocket, net_buf, cliAddr, addrlen))
    {
      break;
    }
  }

  while(1)
  {
    printf("\n***** MENU *****\n");
    printf("1. List All Downloaded Files\n2. List All Files on server\n3. Download\n4. Upload\n5. Exit\n");
    printf("***** END *****\n");
    printf("< user >@userDrive$: ");
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
              return EXIT_SUCCESS;

      default: printf("Invalid choice !!! TRY AGAIN \n");

    }

  }

  return EXIT_SUCCESS;
}
