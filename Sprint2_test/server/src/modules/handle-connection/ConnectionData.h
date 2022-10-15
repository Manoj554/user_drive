extern typedef struct connection_data
{
    int clientSocket;
    char *net_buf;
    struct sockaddr_in serverAddr;
    int addr_size;

}connec_data_t;
