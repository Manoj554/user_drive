/*
*
*
*File name : Authentication.c
*
*
*Author : Team 4
*
*
Description : Sends the username and password to server for authenticattion and permission check.
*
*
*
*/

#include "../../client.h"

int authentication_request(int sockfd,char *net_buf)
{
    char username[20];
    char password[20];
    int failed_count_username = 0;
    int failed_count_password = 0;

    while(1)
    {
        if(failed_count_username >= 3 || failed_count_password >=3)
        {
            break;
        }

        printf("[+] Enter username: ");
        scanf("%s",username);
        
        /*Sending Request to Server*/
        //clearBuf(net_buf);
        strcpy(net_buf,AUTH_REQUEST);
        send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        clearBuf(net_buf);

        /*Sending Username*/
        strcpy(net_buf,username);
        send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        clearBuf(net_buf);
        /*Receiving Acknowlegment of User in Database*/
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        /*If user is not  present send again for authentication*/
        if(strcmp(net_buf,CMD_NOT_SUCCESS)==0)
        {
            failed_count_username++;
            printf("[failed] No such user found: %d attempts left!!!\n",(3 - failed_count_username));
            continue;
        }
        
        printf("[+] Password for %s: ", username);
        scanf("%s",password);
        /*Sending Password*/
        strcpy(net_buf,password);
        send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        clearBuf(net_buf);
        
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        /*If wrong password entered send again for authentication*/
        if(strcmp(net_buf,CMD_NOT_SUCCESS)==0)
        {

            failed_count_password++;
            printf("[failed] Wrong password: %d attempts left!!!\n",(3-failed_count_password));
            continue;
        }
	/*permissions*/
   	clearBuf(net_buf);
	
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
	strcpy(permission,net_buf);	
	printf("Permissions Received : %s\n",permission);   
        printf("[ok] Logged in successfully \n");   
        return 0;
    }

    return -1;
}
