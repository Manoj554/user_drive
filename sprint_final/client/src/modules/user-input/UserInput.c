#include "../../client.h"

void printMenu()
{
  printf("\n\n==================== MENU ====================\n"); //46 characters
  printf("--------------------SELECT--------------------\n\n");
  printf("[+] 1. List all downloaded files \n");
  printf("[+] 2. List all  files on server \n");
  printf("[+] 3. To download a file \n");
  printf("[+] 4. To upload a file \n");
  printf("[+] 5. To delete a file \n");
  printf("[+] 6. Logout \n\n");
  printf("====================  END ====================\n");

  printf("\n[+] Enter your choice :- ");


}

int UserInputValidation(int sockfd,char *net_buf,int addrlen, char *file_name)
{
  while(1)
  {
    char input[50];
    char choice;
  
    printMenu();

    scanf("%s", input);

    if(strlen(input) > 1)
    {
      printf("[error] Invalid input!!! please choose a number from the menu \n");
      continue;
    }
    
    choice = *input;

    switch(choice)
    {
      case '1': ListAllDownloaded();
              break;

      case '2': ListAllDriveFiles(sockfd,net_buf,addrlen);
              break;


      case '3': if(permission[0] == 'r' && permission[1] == 'e')
                    {
                        Download(sockfd,net_buf,addrlen,file_name);
                    }
                    else
                    {
                    printf("Access Denied\n");
                    }
                    break;


      case '4': if(permission[2] == 'w' && permission[3] == 'r')
                    {
                        Upload(sockfd,net_buf,addrlen);
                    }
                    else
                    {
                        printf("Access Denied\n");
                    }
                    break;

      case '5': if(permission[4] == 'd' && permission[5] == 'e')
                    {
                        Delete(sockfd,net_buf,addrlen);
                    }
                    else
                    {
                        printf("Access Denied\n");
                    }
                    break;

      case '6':
              printf("[ok] Successfully loggedout!!! \n"); 
              EndConnection(sockfd,net_buf,addrlen);
              return 0;

      default: printf("[error] Invalid input!!! please choose a number from above menu \n");

    }

  }
}

