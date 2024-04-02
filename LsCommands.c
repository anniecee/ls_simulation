#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "LsCommands.h"

int lsOptions(bool flag_i, bool flag_l, char *directory) {
    if (flag_i && flag_l) {
        // ilOption(directory);
    }
    else if (flag_i) {
        iOption(directory);
    }
    else if (flag_l) {
        // lOption(directory);
    }
    else {
        lsDefault(directory);
    }
}


int lsDefault(char *directory) {
    struct dirent *dp;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Print file name
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            printf("%s  ", dp->d_name);
        }
    }
    printf("\n");

    closedir(dir);
    return 0;
}

int iOption(char *directory) {
    
    struct dirent *dp;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    
    while ((dp = readdir(dir)) != NULL) {
        struct stat fileStat;

        // Create full path for files
        char full_path[1000];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory, dp->d_name);

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        if (stat(full_path, &fileStat) < 0) {
            perror("Error getting file status");
            return 1;
        }

        // Print inode and file name
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') {
            printf("%ld %s  ", (long) fileStat.st_ino, dp->d_name);
        }
    }
    printf("\n");

    closedir(dir);
    return 0;
}

int lOption(char *directory);
int ilOption(char *directory);
