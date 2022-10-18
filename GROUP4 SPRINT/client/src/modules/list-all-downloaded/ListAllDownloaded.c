/*
*
*
*File name : ListAllDowloaded.h
*
*
*Author : Team 4
*
*
Description : Used to display the files present on the client's user-drive-download-files. 
*
*
*
*/

#ifndef __HEADER__
#include "../../client.h"
#endif

void list_all_downloaded()
{
    printf("[+] All downloaded files \n");

    DIR *d;
    struct dirent *dir;
    d = opendir("./users-drive-download-files/");
    if (d)
    {
        int cnt = 0;
        printf("\n*************** Data Received ****************\n");
        while ((dir = readdir(d)) != NULL)
        {
            printf("--> %s\n", dir->d_name);
            cnt++;
        }

        printf("\n[+] %d items found !!! \n", cnt);
        closedir(d);
        printf("\n**********************************************\n");
    }
    else
    {
        printf("[-] No data found!!! \n");
    }
}
