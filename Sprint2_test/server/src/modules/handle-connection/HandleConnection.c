#include "../../server.h"

typedef struct connection_data
{
    int clientSocket;
    char *net_buf;
    struct sockaddr_in serverAddr;
    int addr_size;

}connec_data_t;


void *HandleConnection(void *new_socket_details)
{
    connec_data_t *parcel_ptr = (connec_data_t *) new_socket_details;

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
            recv(clientSocket,net_buf,NET_BUF_SIZE,sendrecvflag);

            printf("Received : %s\n",net_buf);
            /*if(strcmp(net_buf,CMD_SUCCESS) == 0 || strcmp(net_buf,CMD_NOT_SUCCESS) == 0 || (net_buf == NULL) )
            {
                clearBuf(net_buf);
                continue;
            }*/
            if(strcmp(net_buf,AUTH_REQUEST)==0)
            {
                Authentication(clientSocket,net_buf,addr_size);
            }

            if(strcmp(net_buf,LIST_DIR)==0)
            {
                ListAll(clientSocket,net_buf,addr_size);
            }
            else if(strcmp(net_buf,PUSH_DOWNLOAD_FILE)==0)
            {
                PushDownloadFile(clientSocket,net_buf,addr_size);
            }
            else if(strcmp(net_buf,PUSH_UPLOAD_FILE)==0)
            {
                GetUserFile(clientSocket,net_buf,addr_size);
            }
            else if(strcmp(net_buf,DELETE) == 0)
            {
                DeleteFile(clientSocket,net_buf,addr_size);
            }
            else if(strcmp(net_buf,END_CONNECTION)==0)
            {
                close(clientSocket);
                break;
            }

        }
        return NULL;
}