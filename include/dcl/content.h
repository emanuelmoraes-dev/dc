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

c_err content_init(Content* content, int alphabet_size, int keys_size);
c_err content_free(Content* content);

#endif
