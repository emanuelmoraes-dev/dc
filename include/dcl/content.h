#ifndef DCL_CONTENT_H_INCLUDED
#define DCL_CONTENT_H_INCLUDED

#include "uc/tags.h"
#include "uc/hash_map.h"
#include "dcl/errors.h"

typedef struct content {
    int alphabet_size;
    int keys_size;
    HashMap alphabet;
    HashMap odds_graph;
} Content;

typedef struct sentences {
    share Content* content;
    owner char** list;
} Sentences;

typedef struct odds {
    share Content* content;
    owner float** graph;
} Odds;

c_err content_init(Content* content, int alphabet_size, int keys_size);
void content_free(Content* content);

#endif
