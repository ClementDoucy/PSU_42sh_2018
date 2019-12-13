/*
** EPITECH PROJECT, 2019
** auto_c_get_files.c
** File description:
** gets the directory content
*/

#include "prompt.h"
#include <dirent.h>
#include <sys/stat.h>

static void count_file(DIR *dirp, char *file, size_t *file_count)
{
    struct dirent *dir_ent = NULL;
    size_t len = strlen(file);

    while ((dir_ent = readdir(dirp)) != NULL)
        if ((len > 0 || dir_ent->d_name[0] != '.') &&
        strncmp(dir_ent->d_name, file, len) == 0)
            (*file_count)++;
    rewinddir(dirp);
}

static void register_files(DIR *dirp, char *file, char **file_tab)
{
    struct dirent *dir_ent = NULL;
    size_t len = strlen(file);
    size_t index = 0;

    while ((dir_ent = readdir(dirp)) != NULL)
        if ((len > 0 || dir_ent->d_name[0] != '.') &&
        strncmp(dir_ent->d_name, file, len) == 0)
            file_tab[index++] = strdup(dir_ent->d_name);
}

static int void_strcmp(const void *a, const void *b)
{
    const char *pa = *(const char **) a;
    const char *pb = *(const char **) b;

    return strcasecmp(pa, pb);
}

char **get_files(char *directory, char *file, size_t *file_count)
{
    char **file_tab = NULL;
    DIR *dirp = opendir(directory);

    if (!dirp)
        return NULL;
    count_file(dirp, file, file_count);
    file_tab = calloc(*file_count + 1, sizeof(char *));
    register_files(dirp, file, file_tab);
    closedir(dirp);
    qsort(file_tab, *file_count, sizeof(char *), void_strcmp);
    return file_tab;
}
