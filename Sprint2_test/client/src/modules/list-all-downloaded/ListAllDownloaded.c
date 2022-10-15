#include "../../client.h"
void ListAllDownloaded()
{
    printf("InsideListALL\n");
    DIR *d;
    struct dirent *dir;
    d = opendir("./users-drive-download-files/");
    if (d)
    {

        printf("\n***********Data Received************\n");
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
        printf("\n************************************\n");
    }
    else
    {
        printf("Part 2 \n");
    }
}