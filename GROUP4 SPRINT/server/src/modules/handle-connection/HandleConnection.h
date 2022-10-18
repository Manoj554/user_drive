/*
*
*
*File name : HandleConnection.h
*
*
*Author : Team 4
*
*
Description : Header file of HandleConection.c to manage the services and connections for each user provided by the server. 
*
*
*
*/

#ifndef __THREAD_HEADER__
#include <pthread.h>
#endif
extern pthread_mutex_t lock;
extern void *handle_connection(void *new_socket_details);