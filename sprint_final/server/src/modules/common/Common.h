/*
*
*
*File name : Common.h
*
*
*Author : Team 4
*
*
Description : Header file for common functions used across all the modules frequently 
*
*
*
*/

#include <stdio.h>
extern void clearBuf(char *b);
extern char Cipher(char ch);
extern int send_file(FILE *fp,char *buf,int s);
extern int recv_file_save(char *buf,int s,char *file_name);