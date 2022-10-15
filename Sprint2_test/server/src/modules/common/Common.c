#include "../../server.h"
void clearBuf(char *b)
{
    int i;
    for(i = 0;i<NET_BUF_SIZE;i++)
    {
        b[i] = '\0';
    }
}
char Cipher(char ch)
{
    return ch ^ cipherKey; //Encryption using XOR
}

int sendFile(FILE *fp,char *buf,int s)
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
int recvFile_save(char *buf,int s,char *file_name)
{
    FILE *fp;
    int i;
    char ch;
    char file_error[] = "File_Not_Found";
    char base_address[FILE_SIZE] = "./shared-storage/";
    strcat(base_address,file_name);
/*    if(strcmp(buf,file_error)==0)
    {
        return;
    }
*/
    fp = fopen(base_address,"wb");
    if(fp == NULL)
    {
        printf("\nFile open error\n");
        return -1;
    }
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
            //sleep(2);
        }
    }

    fclose(fp);
    return 0;
}