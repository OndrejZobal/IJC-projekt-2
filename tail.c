#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULE_NAME "tail"
#define LINES_DEFAULT 10
#define LINE_LENGTH_LIMIT 4095

struct params {
    int lines;
    char* file;
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
    int length;

    // Alocate buffer for lines.
    char **lastLines = malloc(sizeof(char) * param->lines);
    size_t *lastLinesLength = malloc(sizeof(size_t) * param->lines);
    // ALlocating space for individual strings.
    for (int i = 0; i < param->lines; i++) {
        lastLines[i] = malloc(sizeof(char) * LINE_LENGTH_LIMIT);
        lastLines[i][0] = '\0';
        lastLinesLength[i] = LINE_LENGTH_LIMIT;
    }

    // Iterating through file and storing last few lines in a cyclical buffer.
    while ((length = getline(&(lastLines[linesIndex]), &(lastLinesLength[linesIndex]), file)) != -1) {
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
    // for (int i = 0; i < param->lines; i++) {
    //     free(lastLines[i]);
    // }
    // free(lastLines);
    // free(lastLinesLength);
}

int main(int argc, char **argv) {
    struct params *param = processArgs(argc, argv);

    FILE *file = tryOpenFile(param->file);

    printLastLines(param, file);
    free(file);
    // No need to free the string, because it points to argv.
    free(param);
}
