/*
 *
 *
 *File name : HandleConnection.c
 *
 *
 *Author : Team 4
 *
 *
Description : It manages the services and connection for each user provided by the server. 
 *
 *
 *
 */

#ifndef __HEADER__
#include "../../server.h"
#endif


typedef struct connection_data
{
    int clientSocket;
    char *net_buf;

}connec_data_t;


void *handle_connection(void *new_socket_details)
{
    connec_data_t *parcel_ptr = (connec_data_t *) new_socket_details;

    int clientSocket;
    char *net_buf;

    clientSocket = parcel_ptr->clientSocket;
    net_buf = parcel_ptr->net_buf ;


    /*Receiving command*/
    while(1)
    {
        recv(clientSocket,net_buf,NET_BUF_SIZE,sendrecvflag);

        printf("[+] Command Received : %s\n",net_buf);

        /*if(strcmp(net_buf,CMD_SUCCESS) == 0 || strcmp(net_buf,CMD_NOT_SUCCESS) == 0 || (net_buf == NULL) )
          {
          clearBuf(net_buf);
          continue;
          }*/
        if(strcmp(net_buf,AUTH_REQUEST)==0)
        {
            authentication(clientSocket,net_buf);
        }

        if(strcmp(net_buf,LIST_DIR)==0)
        {
            list_all(clientSocket,net_buf);
        }
        else if(strcmp(net_buf,PUSH_DOWNLOAD_FILE)==0)
        {
            pthread_mutex_lock(&lock);
            push_download_file(clientSocket,net_buf);
            pthread_mutex_unlock(&lock);
        }
        else if(strcmp(net_buf,PUSH_UPLOAD_FILE)==0)
        {
            pthread_mutex_lock(&lock);
            get_user_file(clientSocket,net_buf);
            pthread_mutex_unlock(&lock);
        }
        else if(strcmp(net_buf,DELETE) == 0)
        {
            pthread_mutex_lock(&lock);
            delete_file(clientSocket,net_buf);
            pthread_mutex_unlock(&lock);
        }
        else if(strcmp(net_buf,END_CONNECTION)==0)
        {
            close(clientSocket);
            break;
        }

    }
    return NULL;
}
