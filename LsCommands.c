#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

#include "LsCommands.h"
///////////////////////// HELPER FUNCTION /////////////////////////
void print_file_info(const char *filename, const struct stat *fileStat) {
    char permission[12] = "";

    // Formatted time
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%b %d %Y %H:%M", localtime(&fileStat->st_mtime));

    // Print permissions
    if (S_ISLNK(fileStat->st_mode)){
        strcat(permission, "l");
    }
    else if (S_ISDIR(fileStat->st_mode)){
        strcat(permission, "d");
    }
    else {
        strcat(permission, "-");
    }
    strcat(permission, (fileStat->st_mode & S_IRUSR) ? "r" : "-");
    strcat(permission, (fileStat->st_mode & S_IWUSR) ? "w" : "-");
    strcat(permission, (fileStat->st_mode & S_IXUSR) ? "x" : "-");
    strcat(permission, (fileStat->st_mode & S_IRGRP) ? "r" : "-");
    strcat(permission, (fileStat->st_mode & S_IWGRP) ? "w" : "-");    
    if (fileStat->st_mode & S_IXGRP){
        strcat(permission, "x");
    }
    else if (fileStat->st_mode & S_ISGID){
        strcat(permission, "S");
    }
    else {
        strcat(permission, "-");
    }
    strcat(permission, (fileStat->st_mode & S_IROTH) ? "r" : "-");
    strcat(permission, (fileStat->st_mode & S_IWOTH) ? "w" : "-");
    strcat(permission, (fileStat->st_mode & S_IXOTH) ? "x" : "-");

    // Print other items
    printf("%s", permission);
    printf(" %ld", fileStat->st_nlink);
    printf(" %-s", getpwuid(fileStat->st_uid)->pw_name);
    printf(" %-s", getgrgid(fileStat->st_gid)->gr_name);
    printf(" %8ld", fileStat->st_size);
    printf(" %s", time_buf);
    printf(" %s", filename);

    // Print symbolic links
    if (S_ISLNK(fileStat->st_mode)) {
        char link_buf[256];
        ssize_t len = readlink(filename, link_buf, sizeof(link_buf) - 1);
        if (len != -1) {
            link_buf[len] = '\0';
            printf(" -> %s", link_buf);
        }
    }
    printf("\n");
}


///////////////////////// FUNCTIONS FOR CHOSEN OPTIONS /////////////////////////
int lsOptions(bool flag_i, bool flag_l, char *directory) {
    if (flag_i && flag_l) {
        ilOption(directory);
    }
    else if (flag_i) {
        iOption(directory);
    }
    else if (flag_l) {
        lOption(directory);
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

    // Print file name, omit "." and ".." and hidden files
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') {
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
    
    // Loop through directory
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

        // Print inode and file name, but omit ".", ".." and hidden files
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') {
            printf("%ld %s  ", (long) fileStat.st_ino, dp->d_name);
        }
    }
    printf("\n");

    closedir(dir);
    return 0;
}

int lOption(char *directory) {
    struct dirent *dp;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Loop through directory
    while ((dp = readdir(dir)) != NULL) {
        // Create full path
        char fullpath[1000];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", directory, dp->d_name);

        // Get file status information
        struct stat fileStat;
        if (lstat(fullpath, &fileStat) == -1) {     // lstat returns info of symbolic link
            perror("Error getting file status");
            continue;
        }

        // Print file info, but omit ".", ".." and hidden files
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') {
            print_file_info(dp->d_name, &fileStat);
        }
    }

    closedir(dir);

    return 0;

}

int ilOption(char *directory) {
    struct dirent *dp;
    DIR *dir = opendir(directory);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Loop through directory
    while ((dp = readdir(dir)) != NULL) {
        // Create full path
        char fullpath[1000];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", directory, dp->d_name);

        // Get file status information
        struct stat fileStat;
        if (lstat(fullpath, &fileStat) == -1) {     // lstat returns info of symbolic link
            perror("Error getting file status");
            continue;
        }

        // Print file info, but omit ".", ".." and hidden files
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_name[0] != '.') {
            printf("%10ld ", (long) fileStat.st_ino);
            print_file_info(dp->d_name, &fileStat);
        }
    }

    closedir(dir);

    return 0;
}
