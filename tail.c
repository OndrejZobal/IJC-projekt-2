#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULE_NAME  "tail"
#define PARAM_FILES_ARRAY_INCEMENT 5

struct params {
    int lines;
    int files_amount;
    int files_size;
    char* files[];
};

void errorExit(){
    fprintf(stderr, "%s: Nelze alokovat paměť na hromadě!\n", MODULE_NAME);
    exit(1);

}

struct params *processArgs(int argc, char **argv) {
    struct params *param = malloc(sizeof(struct params));
    if (param == NULL) {
        errorExit();
    }
    param->lines = 0;
    param->files_amount = 0;

    // Iterate throught every argumet
    for(int i = 0; i < argc; i++) {
        // Check if current arg is "-n"
        if(!strcmp(argv[i], "-n")) {
            // Make sure there is at least one more arg.
            if (argv[i+1] == NULL) {
                fprintf(stderr, "%s: A \"-n\" is supposed to be followed by a number!\n", MODULE_NAME);
                exit(1);
            }

            // Try to process the next arg as a number
            int n = strtol(argv[i], NULL, 10);
            if (n < 0) {
                fprintf(stderr, "%s: Invalid \"-n\" parameter!\n", MODULE_NAME);
                exit(1);
            }
            param->lines = n;
            continue;
        }

        // argv[i] is a file path.

        // Allocate more space for param->files if ran out.
        if (param->files_amount+1 => param->files_size) {

        }


    }

    return param;
}

int main(int argc, char **argv) {
    printf("Hello world");

    struct params *param = processArgs(argc, argv);

}
