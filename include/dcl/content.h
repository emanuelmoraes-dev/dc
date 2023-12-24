#ifndef DCL_CONTENT_H_INCLUDED
#define DCL_CONTENT_H_INCLUDED

#include "uc/tags.h"
#include "uc/hash_map.h"
#include "dcl/errors.h"
#include <stdbool.h>

#define CONTENT_CAPACITY_FACTOR (3)
#define HASH_MAP_CAPACITY_FACTOR (1 + UC_HASH_MAP_SIZE_FACTOR)

typedef struct dcl_content {
    int alphabet_size;
    int keys_size;
    UcHashMap alphabet;
    UcHashMap odds_graph;
} DclContent;

typedef struct sentences {
    int size;
    owner char** list;
} DclSentences;

typedef struct odds {
    borrow DclContent* content;
    owner float** graph;
} DclOdds;

c_err dcl_content_init(DclContent* content, int alphabet_size, int keys_size);

bool dcl_content_alphabet_contains_key(const DclContent* content, const char* key);
c_err dcl_content_alphabet_set_key(DclContent* content, owner char* key);
c_err dcl_content_alphabet_add_sentence(DclContent* content, const char* key, owner char* sentence);
c_err dcl_content_alphabet_borrow_sentences(const DclContent* content, const char* key, borrow DclSentences* sentences);

bool dcl_content_graph_contains_key1(const DclContent* content, const char* key1);
c_err dcl_content_graph_set_key1(DclContent* content, owner char* key1);
bool dcl_content_graph_contains_key2(const DclContent* content, const char* key1, const char* key2);
c_err dcl_content_graph_set_key2(DclContent* content, const char* key1, owner char* key2);
c_err dcl_content_graph_borrow_odds(const DclContent* content, const char* key1, const char* key2, borrow DclOdds* odds);
c_err dcl_content_graph_set_odds(DclContent* content, const char* key1, const char* key2, int index1, int index2, float odds_value);

void dcl_content_free(DclContent* content);

#endif
