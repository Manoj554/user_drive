#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <dirent.h>
#include <pthread.h>

#define SA struct sockaddr_in

#define IP_ADDRESS "192.168.56.101"
#define IP_PROTOCOL 0
#define PORT_NO     5556
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define SEND_RECEIVE_FLAG 0
#define FILE_NAME_SIZE 100
#define nofile "File_Not_Found"
#define EOL "\n"

#define ERROR_EXIT -1

/*Commands*/
#define AUTHENTICATE "Authenticate"
#define END_CONNECTION "End_Connection"
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"
