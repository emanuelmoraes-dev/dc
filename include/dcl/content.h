#ifndef DCL_CONTENT_H_INCLUDED
#define DCL_CONTENT_H_INCLUDED

#include "uc/tags.h"
#include "dcl/errors.h"

typedef struct content {
    int alphabet_size;
    owner char** alphabet;
    owner float** odds_graph;
    int dimensions;
} Content;

c_err content_init(Content* content, int alphabet_size, int dimensions);
c_err content_set_sentence(Content* content, move char* sentence, int index);
c_err content_set_odds(Content* content, int si1, int si2, float odds);
void content_free(Content* content);

#endif
