#include <stdio.h>
extern void clearBuf(char *b);
extern char Cipher(char ch);
extern int sendFile(FILE *fp,char *buf,int s);
extern int recvFile_save(char *buf,int s,char *file_name);