/*
*
*
*File name : Common.c
*
*
*Author : Team 4
*
*
Description : Contains common functions used across all the modules frequently 
*
*
*
*/

#ifndef __HEADER__
#include "../../server.h"
#endif

/*
*
*
*Function name : clearBuf()
*
*
*Author : Team 4
*
*
Description : Set all memory values to ‘\0’ of the char pointer.
*
*
*
*/

void clearBuf(char *b)
{
    int i;
    for(i = 0;i<NET_BUF_SIZE;i++)
    {
        b[i] = '\0';
    }
}
/*
*
*
*Function name : Cipher()
*
*
*Author : Team 4
*
*
Description : Used to encrypt and decrypt the file based on the XOR operation and cipher key.
*
*
*
*/

char Cipher(char ch)
{
    return ch ^ cipherKey; //Encryption using XOR
}

/*
*
*
*Function name : send_file()
*
*
*Author : Team 4
*
*
Description : Used to encrypt the contents of the file to be sent.
*
*
*
*/


int send_file(FILE *fp,char *buf,int s)
{
    int i, len;
    if(fp==NULL)
    {
        strcpy(buf,nofile);
        len = strlen(nofile);
        buf[len] = EOF;
        for(i = 0;i<=len;i++)
        {
            buf[i] = Cipher(buf[i]);
        }
        return 1;
    }
    char ch,ch2;
    for(i =0;i<s;i++)
    {
        ch = fgetc(fp);
        ch2 = Cipher(ch);
        buf[i] = ch2;
        if(ch == EOF)
            return 1;
    }

    return 0;
}


/*
*
*
*Function name : recv_file_save()
*
*
*Author : Team 4
*
*
Description : Used to save the file on server with the specified filename by user.
*
*
*
*/


int recv_file_save(char *buf,int s,char *file_name)
{
    FILE *fp;
    int i;
    char ch;
    char base_address[FILE_SIZE] = "./shared-storage/";
    strcat(base_address,file_name);
    fp = fopen(base_address,"w+");
    if(fp == NULL)
    {
        printf("\nFile open error\n");
        return -1;
    }

    //character-by-character encryption and saving file
    for(i = 0;i<s;i++)
    {
        ch = buf[i];
        ch = Cipher(ch);
        if(ch == EOF)
        {
            return 1;
        }
        else
        {
            fputc(ch,fp);
            printf("%c",ch);
        }
    }

    fclose(fp);
    return 0;
}
