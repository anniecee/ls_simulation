#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "LsCommands.h"


int main(int argc, char* argv[]) {

    bool flag_i = false;
    bool flag_l = false;
    bool flag_error = false;

    char *directory = NULL;

    if (argc == 1) {
        directory = ".";
        lsOptions(flag_i, flag_l, directory);
    }
    else {
        // Loop through all arguments to get inputs
        for (int i = 1; i < argc; i++) {
            char *input = argv[i];

            if (directory != NULL) {
                printf("Error, directory should come after any options\n");
                flag_error = true;
                break;
            }
            
            // Check if flag -i and/or flag -l are called
            else if (input[0] == '-') {
                for (int j = 1; j < strlen(input); j++) {
                    if (input[j] == 'i') {
                        flag_i = true;
                    }
                    if (input[j] == 'l') {
                        flag_l = true;
                    }
                }
            }

            else {
                directory = input;
            }
        }

        // If no directory input, set to current directory
        if (directory == NULL) {
            directory = ".";
        }

        // Call ls function
        if (!flag_error) {
            lsOptions(flag_i, flag_l, directory);
        }
    }


    // struct dirent *dp;
    // DIR *dir = opendir(".");

    // if (dir == NULL) {
    //     perror("Error opening directory");
    //     return 1;
    // }

    // while ((dp = readdir(dir)) != NULL) {
    //     if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
    //         printf("%s  ", dp->d_name);
    //     }
    // }
    // printf("\n");

    // closedir(dir);

    return 0;
}
