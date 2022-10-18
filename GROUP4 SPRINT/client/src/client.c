/*
 *
 *
 *File name : client.c
 *
 *
 *Author : Team 4
 *
 *
 * Description : Initializing and setting pararametrs of client for connection with server
 *
 *
 *
 */

#ifndef __HEADER__
#include "./client.h"
#endif

char permission[30];
int main()
{
    int choice;

    // char array to store incoming and outgoing message
    char net_buf[NET_BUF_SIZE]; /* Used for Data and Command Transfer*/
    char file_name[FILE_SIZE];/* Requested File Name */
    socklen_t addrlen;// = sizeof(addr_con);
                      // Socket id
    int clientSocket, ret;

    // Client socket structure
    struct sockaddr_in cliAddr;

    struct sockaddr_in serverAddr;


    // Creating socket id
    clientSocket = socket(AF_INET,
            SOCK_STREAM, 0);

    if (clientSocket < 0) {
        perror("[error] Socket");
        exit(EXIT_FAILURE);
    }

    printf("[ok] Socket is created.\n");

    // Initializing socket structure with NULL
    memset(&cliAddr, '\0', sizeof(cliAddr));


    // Assigning port number and IP address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);

    serverAddr.sin_addr.s_addr
        = inet_addr(IP_ADDRESS);

    // connect() to connect to the server
    ret = connect(clientSocket,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    if (ret < 0) {
        perror("[error] Connection");
        exit(EXIT_FAILURE);
    }


    printf("[ok] Connected to server.\n");
    printf("[ok] Please login to continue ... \n");

    int auth_check = authentication_request(clientSocket,net_buf);

    if(auth_check != 0)
    {
        printf("[failed] multiple login attempt and failed!!! \n");
        end_connection(clientSocket,net_buf);
        return -1;
    }

    user_choice(clientSocket,net_buf,file_name);

    return EXIT_SUCCESS;
}
