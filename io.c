#include <stdio.h>
#include <ctype.h>

int read_word(char *s, int max, FILE *f){
    int c;
    int i = 0;
    while ((c = getc(f)) != EOF) {
        if (isspace(c) || i == max-1) {
            break;
        }
        s[i++] = c;
    }
    s[i] = '\0';
    return (c == EOF) ? EOF : i;
}
