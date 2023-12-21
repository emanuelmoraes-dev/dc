#ifndef DCL_CONTENT_H_INCLUDED
#define DCL_CONTENT_H_INCLUDED

#include "uc/tags.h"
#include "uc/hash_map.h"
#include "dcl/errors.h"
#include <stdbool.h>

typedef struct content {
    int alphabet_size;
    int keys_size;
    HashMap alphabet;
    HashMap odds_graph;
} Content;

typedef struct sentences {
    int size;
    owner char** list;
} Sentences;

typedef struct odds {
    borrow Content* content;
    owner float** graph;
} Odds;

c_err content_init(Content* content, int alphabet_size, int keys_size);

c_err content_alphabet_set_key(Content* content, move char* key);
bool content_alphabet_contains_key(const Content* content, const char* key);
c_err content_alphabet_add_sentence(Content* content, const char* key, move char* sentence);
c_err content_alphabet_borrow_sentences(Content* content, const char* key, borrow Sentences* sentences);

c_err content_graph_set_key1(Content* content, move char* key1);
bool content_graph_contains_key1(Content* content, const char* key1);
c_err content_graph_set_key2(Content* content, const char* key1, move char* key2);
bool content_graph_contains_key2(Content* content, const char* key1, const char* key2);
c_err content_graph_set_odds(Content* content, const char* key1, const char* key2, int index1, int index2, float odds);
c_err content_graph_borrow_odds(Content* content, const char* key1, const char* key2, borrow Odds* odds);

void content_free(Content* content);

#endif
