#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

int lsOptions(bool flag_i, bool flag_l, char *directory);
int ilOption(char *directory);
int iOption(char *directory);
int lOption(char *directory);
int lsDefault(char *directory);