#include "sdmllang.h"


int sdml_strncpy(char *dest, char *src, size_t size)
{
    if (!dest || !src) return (0);
    size_t destSize = sdml_strlen(dest);
    for (size_t i = 0; src[i] || i > size; i++)
    {
        dest[destSize + i] = src[i];
    }
    dest[destSize + size] = '\0';
    return (1);
}

char *getWholeFile(char *name, size_t *size)
{
    char buff[FILEREADSIZE];
    int fd = -1;
    if ((fd = open(name, O_RDONLY)) == -1) return (close(fd), NULL);
    ssize_t readRet = 0;
    char *retBuff = NULL;
    while ((readRet = read(fd, buff, FILEREADSIZE)) > 0)
    {
        if (!retBuff)
            retBuff = calloc(FILEREADSIZE + 1, sizeof(char));
        else
            retBuff = realloc(retBuff, sizeof(retBuff) + FILEREADSIZE + 1);
        if (!retBuff) return (close(fd), NULL);
        if (!sdml_strncpy(&retBuff[sdml_strlen(retBuff)], buff, sdml_strlen(buff))) return (close(fd), free(retBuff), NULL);
        size += readRet;
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
        headSeaking->content = getWholeFile(names[i], &headSeaking->size);
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