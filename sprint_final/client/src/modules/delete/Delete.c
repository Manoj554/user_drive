#include "../../client.h"
void Delete(int sockfd,char *net_buf,int addrlen)
{

    int nBytes;
    FILE *fp;
    char *file_name;
    clearBuf(net_buf);
    strcpy(net_buf,DELETE);
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);
    printf("\n[+] Please Enter file name to be deleted....\n");
    scanf("%s",net_buf);
    if(strcmp(net_buf,EXIT)==0)
    {
        printf("[failed] you can't use %s as filename \n", EXIT);
        return;
    }
    send(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);
    clearBuf(net_buf);

    recv(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag);

    if(strcmp(net_buf,CMD_SUCCESS)==0)
    {
        printf("[ok] File Deleted Sucessfully\n");
    }
    else
    {
        printf("%s\n",nofile);
    }
}
