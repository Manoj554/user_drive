/*
*
*
*File name : Authentication.h
*
*
*Author : Team 4
*
*
Description : Header file of Authentication.c,used to checks for the username and password in user database and provides permission to client. 
*
*
*
*/

extern char permission[30];
extern int authentication_request(int sockfd,char *net_buf);