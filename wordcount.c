// 2) wordcount.c
// Ondřej Zobal (xzobal01)
// FIT VUT v Brně
// 15.4.2022

#include "htab.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

#define HTAB_SIZE 1000
#define LINE_LIMIT 127

void print_pair(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    htab_t *htab = htab_init(HTAB_SIZE);
    char *word = malloc(LINE_LIMIT);
    if (word == NULL) {
        fprintf(stderr, "Cannot allocate memory!\n");
        exit(1);
    }

    while(read_word(word, LINE_LIMIT, stdin) != EOF) {
        if(word[0] == '\0') {
            continue;
        }
        htab_lookup_add(htab, word)->value++;
    }

    htab_for_each(htab, &print_pair);

    htab_free(htab);
    free(word);
}
