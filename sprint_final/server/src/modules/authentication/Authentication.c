/*
*
*
*File name : Authentication.c
*
*
*Author : Team 4
*
*
Description : Checks for the username and password in user database and provides permission to client. 
*
*
*
*/

#include "../../server.h"
#include <netinet/in.h>

/*structure to hold user info and permissions*/
struct account {
    char id[20];
    char password[20];
    char read[10];
    char write[10];
    char delete[10];
};
static struct account accounts[10];

int read_file(struct account accounts[])
{
    FILE *fp;
    int i=0;   // count how many lines are in the file
    int c;
    fp=fopen("./server-files/UserDB", "r");
    while(!feof(fp)) {
        c=fgetc(fp);
        if(c=='\n')
            ++i;
    }
    int j=0;
    rewind(fp); 
        // read each line and put into accounts
    while(j!=i-1) {
        fscanf(fp, "%s %s %s %s %s", accounts[j].id, accounts[j].password, accounts[j].read, accounts[j].write, accounts[j].delete);
        ++j;
    }
    return ((i/2) + 1);
}

/*Authentication of user*/
void authentication(int sockfd,char *net_buf)
{
    int total_entries = read_file(accounts);
    printf("[+] Authentication process start from client sockfd %d \n", sockfd);
    char username[20];
    char password[20];
    char permission[30];

       /*Attending Request of Username From Client*/
        clearBuf(net_buf);
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        for(int i = 0;i<total_entries;i++)
        {
            if(strcmp(accounts[i].id,net_buf)==0)
            {
                strcpy(username,net_buf);
                strcpy(password,accounts[i].password);
		strcpy(permission,accounts[i].read);
		strcat(permission,accounts[i].write);
		strcat(permission,accounts[i].delete);

            }
        }
        printf("[+] username received : %s\n",net_buf);
        if(strcmp(username,net_buf) == 0)
        {
            strcpy(net_buf,CMD_SUCCESS);
            send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
            clearBuf(net_buf);
            recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        printf("[+] password received : %s\n",net_buf);

            /*Attending Request of Correct Password From Client*/
            if(strcmp(password,net_buf)==0)
            {
                clearBuf(net_buf);
                strcpy(net_buf,CMD_SUCCESS);
                send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        printf("[+]Data sent : %s\n",net_buf);

		clearBuf(net_buf);
		strcpy(net_buf,permission);
                send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
            }
            else
            {
                clearBuf(net_buf);
                strcpy(net_buf,CMD_NOT_SUCCESS);
                send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
            }

        }
        else
        {

           clearBuf(net_buf);
            strcpy(net_buf,CMD_NOT_SUCCESS);
            send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        }

}
