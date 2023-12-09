#include <stdlib.h>
#include "dc/lib/content.h"

void __content_free_alphabet(Content* content);
void __content_free_odds_grath(Content* content);

void content_free(Content* content) {
    __content_free_alphabet(content);
    __content_free_odds_grath(content);
}

void __content_free_alphabet(Content* content) {
    if (content->alphabet_size <= 0 || content->alphabet == NULL) {
        return;
    }

    for (int i = 0; i < content->alphabet_size; ++i) {
        char* symbol = content->alphabet[i];
        if (symbol != NULL) {
            free(symbol);
        }
    }

    free(content->alphabet);
}

void __content_free_odds_grath(Content* content) {
    if (content->alphabet_size <= 0 || content->odds_graph == NULL) {
        return;
    }

    for (int i = 0; i < content->alphabet_size; ++i) {
        float* odds = content->odds_graph[i];
        if (odds != NULL) {
            free(odds);
        }
    }

    free(content->odds_graph);
}
