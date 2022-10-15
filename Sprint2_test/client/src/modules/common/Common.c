#include "../../client.h"
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
int recvFile_save(char *buf,int s,char *file_name)
{
    FILE *fp;
    int i;
    char ch;
    char file_error[] = "File_Not_Found";
    char base_address[FILE_SIZE] = "./users-drive-download-files/";
    strcat(base_address,file_name);
    /*    if(strcmp(buf,file_error)==0)
          {
          return;
          }
          */
    fp = fopen(base_address,"w+");

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

int recvFile(char *buf,int s)
{
    int i;
    char ch;
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
            printf("%c",ch);
            //sleep(2);
        }
    }

    return 0;
}
int file_found(char *buf,int s)
{
    char file_error[] = "File_Not_Found";
    char string[strlen(buf) - 1];
    int i = 0;
    for(i=0;i<strlen(buf)-1;i++)
    {
        string[i] = Cipher(buf[i]);
    }

    printf("String: %s\n",string);
    if(strcmp(string,file_error)==0)
    {
        return -1;
    }

    return 0;
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
