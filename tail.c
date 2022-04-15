#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MODULE_NAME "tail"
#define LINES_DEFAULT 10
#define LINE_LENGTH_LIMIT 4096

struct params {
    int lines;
    char *file;
};

void memoryError(){
    fprintf(stderr, "%s: Nelze alokovat paměť na hromadě!\n", MODULE_NAME);
    exit(1);
}

struct params *processArgs(int argc, char **argv) {
    struct params *param = malloc(sizeof(struct params));
    if (param == NULL) {
        memoryError();
    }
    param->lines = LINES_DEFAULT;
    param->file = NULL;

    // Iterate throught every argumet
    for(int i = 1; i < argc; i++) {
        // Check if current arg is "-n"
        if(!strcmp(argv[i], "-n")) {
            // Make sure there is at least one more arg.
            if (argv[i+1] == NULL) {
                fprintf(stderr, "%s: A \"-n\" is supposed to be followed by a number!\n", MODULE_NAME);
                exit(1);
            }

            // Try to process the next arg as a number
            int n = strtol(argv[++i], NULL, 10);
            if (n < 0) {
                fprintf(stderr, "%s: Invalid \"-n\" parameter!\n", MODULE_NAME);
                exit(1);
            }
            param->lines = n;
            continue;
        }

        // argv[i] is a file path.

        // Make sure the file has not yet been set.
        if(param->file != NULL) {
            fprintf(stderr, "%s: Reading from more files is not supported!\n", MODULE_NAME);
            exit(1);
        }
        // To make things simpler I am storing ptrs to the original cmd arguments.
        param->file = argv[i];
    }

    return param;
}

/**
 * Returns a file descriptor or exits.
 */
FILE *tryOpenFile(const char *path) {
    // If no path was specified, reading from stdin.
    if (path == NULL) {
        return stdin;
    }

    FILE *file = fopen(path, "r");
    if(file == NULL) {
        fprintf(stderr, "%s: File \"%s\" cannot be open for reading\n", MODULE_NAME, path);
        exit(1);
    }

    return file;
}

void printLastLines(struct params *param, FILE *file) {
    int linesIndex = 0;

    // Alocate buffer for lines.
    char **lastLines = malloc(sizeof(char*) * param->lines);
    if (lastLines == NULL) {
        memoryError();
    }

    // ALlocating space for individual strings.
    for (int i = 0; i < param->lines; i++) {
        lastLines[i] = malloc(sizeof(char) * LINE_LENGTH_LIMIT);
        if (lastLines[i] == NULL) {
            memoryError();
        }
        lastLines[i][0] = '\0';
    }

    bool cutLineWarn = false;
    // iterating through file and storing last few lines in a cyclical buffer.
    while ((fgets(lastLines[linesIndex], LINE_LENGTH_LIMIT, file)) != NULL) {
        // check if string contains \n
        bool whole = false;
        for(int j = 0; j < LINE_LENGTH_LIMIT; j++) {
            if (lastLines[linesIndex][j] == '\0') {
                lastLines[linesIndex][j-1] = '\n';
                break;
            }
            if(lastLines[linesIndex][j] == '\n') {
                whole = true;
                break;
            }
        }

        // If the line wanst read in full, jump to the next line
        if (!whole) {
            if(!cutLineWarn) {
                fprintf(stderr, "%s: Some lines in this file exceed limit of %d and will be cut!\n",
                        MODULE_NAME, LINE_LENGTH_LIMIT);
                cutLineWarn = true;
            }
            int c = 0;
            while ((c = fgetc(file)) != EOF) {
                if(c == '\n'){
                    break;
                }
            }
        }


        linesIndex++;
        if (linesIndex == param->lines) {
            linesIndex = 0;
        }
    }

    // Printing last lines.
    for (int i = 0; i < param->lines; i++) {
        printf("%s", lastLines[linesIndex++]);
        if(linesIndex == param->lines) {
            linesIndex = 0;
        }
    }

    // Cleanup
    for (int i = 0; i < param->lines; i++) {
        free(lastLines[i]);
    }
    free(lastLines);
}

int main(int argc, char **argv) {
    struct params *param = processArgs(argc, argv);

    FILE *file = tryOpenFile(param->file);

    printLastLines(param, file);

    // No need to free the string, because it points to argv.
    free(param);
    fclose(file);
}
