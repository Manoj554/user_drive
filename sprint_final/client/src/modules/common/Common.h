#include <stdio.h>
extern void clearBuf(char *b);
extern char Cipher(char ch);
extern int recvFile_save(char *buf,int s,char *file_name);
extern int recvFile(char *buf,int s);
extern int file_found(char *buf,int s);
extern int sendFile(FILE *fp,char *buf,int s);
extern void EndConnection(int sockfd,char *net_buf,int addrlen);
