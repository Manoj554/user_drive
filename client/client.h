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

#define SA struct sockaddr_in 

#define FILE_SIZE 100
#define IP_PROTOCOL 0
#define PORT_NO     5556
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define EXIT "exit"
#define IP_ADDRESS  "192.168.56.101"
#define nofile "File_Not_Found"


/*Commands*/
#define AUTHENTICATE "Authenticate"
#define END_CONNECTION "End_Connection"
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"

#if 0
typedef struct sendRequest
{
  char cmd[20];
  char data[NET_BUF_SIZE];

}req_obj_t;
#endif

