/*
*
*
*File name : server.h
*
*
*Author : Team 4
*
*
Description : Header file containing all includes of the modules and commands as MACROS 
*
*
*
*/

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

/*Modules Included*/
#include "./modules/handle-connection/HandleConnection.h"
#include "./modules/delete-file/DeleteFile.h"
#include "./modules/authentication/Authentication.h"
#include "./modules/common/Common.h"
#include "./modules/list-all/ListAll.h"
#include "./modules/push-download-file/PushDownloadFile.h"
#include "./modules/get-user-file/GetUserFile.h"

/*Commands*/
#define END_CONNECTION "End_Connection"
#define LIST_DIR "List_Directory"
#define PUSH_DOWNLOAD_FILE "Download"
#define PUSH_UPLOAD_FILE "Upload"
#define DELETE "Delete"
#define AUTH_REQUEST "Auth"
#define CMD_SUCCESS "done"
#define CMD_NOT_SUCCESS "notdone"


#define FILE_SIZE 100
#define IP_ADDRESS "192.168.56.101"
#define IP_PROTOCOL 0
#define PORT_NO     5556
#define NET_BUF_SIZE 40960
#define cipherKey 'S'
#define sendrecvflag 0
#define FILE_NAME_SIZE 100
#define nofile "File_Not_Found"
#define EOL "\n"
