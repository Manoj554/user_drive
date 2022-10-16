
/*
*
*
*File name : Common.h
*
*
*Author : Team 4
*
*
Description : Header files of common functions used across all the modules frequently 
*
*
*
*/

#include <stdio.h>
extern void clearBuf(char *b);
extern char Cipher(char ch);
extern int save_file(char *buf,int s,char *file_name);
extern int recv_file(char *buf,int s);
extern int file_found(char *buf,int s);
extern int send_file(FILE *fp,char *buf,int s);
extern void end_connection(int sockfd,char *net_buf);
