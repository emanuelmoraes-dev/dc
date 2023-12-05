#include <stdlib.h>
#include "dc/content.h"

dc_error __content_init_alphabet(Content* content);
dc_error __content_init_odds_graph(Content* content);

dc_error content_init(Content* content, int alphabet_size, int dimensions) {
    content->alphabet_size = alphabet_size;
    content->alphabet = NULL;
    content->odds_graph = NULL;
    content->dimensions = dimensions;

    dc_error error = __content_init_alphabet(content);

    if (error != DC_OK) {
        content_free(content);
        return error;
    }

    error = __content_init_odds_graph(content);

    if (error != DC_OK) {
        content_free(content);
        return error;
    }

    return DC_OK;
}

dc_error __content_init_alphabet(Content* content) {
    content->alphabet = (char**) malloc(sizeof(char*) * content->alphabet_size);

    if (content->alphabet == NULL) {
        return DC_ERR_THROW_ALLOC(DC_ERR_ARG_ALLOC_ALPHABET);
    }

    for (int i = 0; i < content->alphabet_size; ++i) {
        content->alphabet[i] = NULL;
    }

    return DC_OK;
}

dc_error __content_init_odds_graph(Content* content) {
    content->odds_graph = (float**) malloc(sizeof(float*) * content->alphabet_size);

    if (content->odds_graph == NULL) {
        return DC_ERR_THROW_ALLOC(DC_ERR_ARG_ALLOC_ODDS_GRAPH);
    }

    for (int i = 0; i < content->alphabet_size; ++i) {
        content->odds_graph[i] = (float*) malloc(sizeof(float) * content->alphabet_size);

        if (content->odds_graph[i] == NULL) {
            return DC_ERR_THROW_ALLOC(DC_ERR_ARG_ALLOC_SENTENCE);
        }

        for (int j = 0; j < content->alphabet_size; ++j) {
            content->odds_graph[i][j] = 0;
        }
    }

    return DC_OK;
}
