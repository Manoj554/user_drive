/*
 *
 *
 *File name : server.c
 *
 *
 *Author : Team 4
 *
 *
 * Description : Initializing and setting pararametrs of concurrent server implemented using threads 
 *
 *
 *
 */

#ifndef __HEADER__
#include "./server.h"
#endif

pthread_mutex_t lock;

typedef struct connection_data
{
    int clientSocket;
    char *net_buf;
    //struct sockaddr_in serverAddr;
    int addr_size;

}connec_data_t;

int main()
{
    char net_buf[NET_BUF_SIZE];
    FILE *fp;
    // Server socket id
    int sockfd, ret;

    // Server socket address structures
    struct sockaddr_in serverAddr;

    // Client socket id
    int clientSocket;

    // Client socket address structures
    struct sockaddr_in cliAddr;

    // Stores byte size of server socket address
    socklen_t addr_size;

    // Child process id
    pid_t childpid;

    // Creates a TCP socket id from IPV4 family
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Error handling if socket id is not valid
    if (sockfd < 0) {
        perror("[error] Connection");
        exit(EXIT_FAILURE);
    }

    printf("[ok] Server socket is created.\n");

    // Initializing address structure with NULL
    memset(&serverAddr, '\0',
            sizeof(serverAddr));

    // Assign port number and IP address
    // to the socket created
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);

    //IP address
    serverAddr.sin_addr.s_addr
        = inet_addr(IP_ADDRESS);

    // Binding the socket id with
    // the socket structure
    ret = bind(sockfd,
            (struct sockaddr*)&serverAddr,
            sizeof(serverAddr));

    // Error handling
    if (ret < 0) {
        perror("[error] Binding");
        exit(EXIT_FAILURE);
    }

    // Listening for connections (upto 10)
    if (listen(sockfd, 10) == 0) {
        printf("[ok] Server is listening\n\n");
    }

    int cnt = 0;


    while(1)
    {
        clientSocket = accept(sockfd, (struct sockaddr*)&cliAddr,&addr_size);

        // Error handling
        if (clientSocket < 0) {
            exit(1);
        }

        // Displaying information of
        // connected client
        printf("[ok] Connection accepted from %s:%d\n",
                inet_ntoa(cliAddr.sin_addr),
                ntohs(cliAddr.sin_port));

        // Print number of clients
        // connected till now
        printf("[ok] Clients connected: %d\n\n",
                ++cnt);

        pthread_t t;

        //arguments to be passed in pthread_create for client handler function 
        connec_data_t *parcel_ptr;
        connec_data_t parcel;
        parcel.clientSocket = clientSocket;
        parcel.net_buf = net_buf;

        parcel_ptr = &parcel;

        
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{
        	printf("\n mutex init has failed\n");
        	return 1;
    	}

        pthread_create(&t,NULL,handle_connection,parcel_ptr);

    }
    return EXIT_SUCCESS;
}
