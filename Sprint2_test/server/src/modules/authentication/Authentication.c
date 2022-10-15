#include "../../server.h"
#include <netinet/in.h>
struct account {
    char id[20];
    char password[20];
    char read[1];
    char write[1];
    char delete[1];
};
static struct account accounts[10];
void read_file(struct account accounts[])
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
    rewind(fp);  // Line I added
        // read each line and put into accounts
    while(j!=i-1) {
        fscanf(fp, "%s %s", accounts[j].id, accounts[j].password);
        ++j;
    }
}

/*Authentication of user*/
void Authentication(int sockfd,char *net_buf,int addrlen)
{
    read_file(accounts);
    printf("%s %s\n", accounts[0].id, accounts[0].password);
    printf("Inside Auth\n");
    char username[20];
    char password[20];

       /*Attending Request of Username From Client*/
        clearBuf(net_buf);
        recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        for(int i = 0;i<4;i++)
        {
            if(strcmp(accounts[i].id,net_buf)==0)
            {
                strcpy(username,net_buf);
                strcpy(password,accounts[i].password);
            }
        }
        printf("2nd : %s\n",net_buf);
        if(strcmp(username,net_buf) == 0)
        {
            strcpy(net_buf,CMD_SUCCESS);
            send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
            clearBuf(net_buf);
            recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
        printf("3nd : %s\n",net_buf);
            /*Attending Request of Correct Password From Client*/
            if(strcmp(password,net_buf)==0)
            {
                clearBuf(net_buf);
                strcpy(net_buf,CMD_SUCCESS);
                send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

        printf("4th : %s\n",net_buf);
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
