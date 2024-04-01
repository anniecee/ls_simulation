#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "LsCommands.h"

int lsOptions(bool flag_i, bool flag_l, char *directory) {
    if (flag_i && flag_l) {
        printf("i+l option. directory: %s \n", directory);
        // ilOption(directory);
    }
    else if (flag_i) {
        printf("i option. directory: %s \n", directory);
        // iOption(directory);
    }
    else if (flag_l) {
        printf("l option. directory: %s \n", directory);
        // lOption(directory);
    }
    else {
        printf("basic option. directory: %s \n", directory);
        // lsDefault(directory);
    }
}

int ilOption(char *directory);
int iOption(char *directory);
int lOption(char *directory);
int lsDefault(char *directory);