/*
 *
 *
 *File name : UserInterface.c
 *
 *
 *Author : Team 4
 *
 *
Description : Provides a menu to the user and sends particular requests based on the user’s input.
 *
 *
 */

#ifndef __HEADER__
#include "../../client.h"
#endif

void print_menu()
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

int user_choice(int sockfd,char *net_buf,char *file_name)
{
    while(1)
    {
        char input[50];
        char choice;

        print_menu();

        scanf("%s", input);

        if(strlen(input) > 1)
        {
            printf("[error] Invalid input!!! please choose a number from the menu \n");
            continue;
        }

        choice = *input;

        switch(choice)
        {
            case '1': list_all_downloaded();
                      break;

            case '2': list_all_drive_files(sockfd,net_buf);
                      break;


            case '3': if(permission[0] == 'r' && permission[1] == 'e')
                      {
                          download(sockfd,net_buf,file_name);
                      }
                      else
                      {
                          printf("Access Denied\n");
                      }
                      break;


            case '4': if(permission[2] == 'w' && permission[3] == 'r')
                      {
                          upload(sockfd,net_buf);
                      }
                      else
                      {
                          printf("Access Denied\n");
                      }
                      break;

            case '5': if(permission[4] == 'd' && permission[5] == 'e')
                      {
                          delete(sockfd,net_buf);
                      }
                      else
                      {
                          printf("Access Denied\n");
                      }
                      break;

            case '6':
                      printf("[ok] Successfully loggedout!!! \n"); 
                      end_connection(sockfd,net_buf);
                      return 0;

            default: printf("[error] Invalid input!!! please choose a number from above menu \n");

        }

    }
}

