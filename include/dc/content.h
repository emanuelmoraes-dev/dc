#ifndef DC_CONTENT_H_INCLUDED
#define DC_CONTENT_H_INCLUDED

#include "dc/tags.h"
#include "dc/errors.h"

typedef struct content {
    int alphabet_size;
    owner char** alphabet;
    owner float** odds_graph;
    int dimensions;
} Content;

dc_error content_init(Content* content, int alphabet_size, int dimensions);
dc_error content_set_sentence(Content* content, move char* sentence, int index);
dc_error content_set_odds(Content* content, int si1, int si2, float odds);
void content_free(Content* content);

#endif
