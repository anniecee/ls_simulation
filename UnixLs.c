#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "LsCommands.h"

int main(int argc, char* argv[]) {

    bool flag_i = false;
    bool flag_l = false;
    bool flag_error = false;
    int number_of_directory = 0;

    char *directory = NULL;

    if (argc == 1) {
        directory = ".";
        lsOptions(flag_i, flag_l, directory);
    }
    else {
        // Loop through all arguments to get inputs
        for (int i = 1; i < argc; i++) {
            char *input = argv[i];
            
            // Check if flag -i and/or flag -l are called
            if (input[0] == '-') {
                if (directory != NULL) {
                    printf("Error, directory should come after any options\n");
                    flag_error = true;
                    break;
                }

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
                number_of_directory++;
            }
        }

        if (directory == NULL) {
            directory = ".";
        }

        // Call ls function
        if (!flag_error) {
            // Print only current directory if user does not enter multiple directories
            if (number_of_directory < 2){
                lsOptions(flag_i, flag_l, directory);
            }
            else{
                for (int i = 1; i < argc; i++){
                    // If no directory input, set to current directory
                    if (argv[i][0] != '-'){
                        printf("%s:\n", argv[i]);
                        lsOptions(flag_i, flag_l, argv[i]);
                        printf("\n");
                    
                    } 
                }
            }
        }
    }

    return 0;
}
