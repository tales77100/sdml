#include "sdmllang.h"


void printFile(File file)
{
    printf("file( %s ) of size( %zu ):\n%s", file.name, file.size, file.content);
}

char *getWholeFile(char *name)
{
    char buff[FILEREADSIZE + 1];
    int fd = -1;
    if ((fd = open(name, O_RDONLY)) == -1) return (close(fd), NULL);
    ssize_t readRet = 0;
    char *retBuff = calloc(FILEREADSIZE * 2, sizeof(char));
    while ((readRet = read(fd, buff, FILEREADSIZE)) > 0)
    {
        buff[readRet] = '\0';
        retBuff = realloc(retBuff, strlen(retBuff) + strlen(buff) + 2);
        if (!retBuff) return (close(fd), NULL);
        if (!strncpy(&retBuff[strlen(retBuff)], buff, strlen(buff))) return (close(fd), free(retBuff), NULL);
    }
    return (close(fd), retBuff);
}

int freeFiles(File *files)
{
    File *temp = files;
    while (temp)
    {
        free(files->content);
        temp = files->next;
        free(files);
        files = temp;
    }
    return (1);
}

File *getFiles(char **names)
{
    File *root = calloc(1, sizeof(*root));
    File *headSeaking = root;
    if (!root) return (NULL);
    for (size_t i = 1; names[i]; i++)
    {
        headSeaking->content = getWholeFile(names[i]);
        headSeaking->size = strlen(headSeaking->content);
        if (!headSeaking->content) return (freeFiles(root), NULL);
        headSeaking->name = names[i];
        if (names[i + 1])
        {
            headSeaking->next = calloc(1, sizeof(*headSeaking->next));
            if (!headSeaking) return (freeFiles(root), NULL);
            headSeaking = headSeaking->next;
        }
    }
    return (root);
}