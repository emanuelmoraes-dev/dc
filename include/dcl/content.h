#ifndef DCL_CONTENT_H_INCLUDED
#define DCL_CONTENT_H_INCLUDED

#include "uc/tags.h"
#include "uc/hash_map.h"
#include "dcl/errors.h"
#include <stdbool.h>

#define __DCL_CONTENT_CAPACITY_FACTOR (3)
#define __UC_HASH_MAP_CAPACITY_FACTOR (1 + UC_HASH_MAP_SIZE_FACTOR)

#define DCL_HASH_MAP_CAPACITY(size, MAX_VALUE) \
    !uc_err_is_overflow_LARGE_MULT(size, __DCL_CONTENT_CAPACITY_FACTOR, MAX_VALUE) \
    ? ((size) * __DCL_CONTENT_CAPACITY_FACTOR) : (\
        !uc_err_is_overflow_LARGE_MULT(size, __UC_HASH_MAP_CAPACITY_FACTOR, MAX_VALUE) \
        ? ((size) * __UC_HASH_MAP_CAPACITY_FACTOR) : (size)\
    )

typedef struct dcl_content {
    int alphabet_size;
    int keys_size;
    UcHashMap alphabet;
    UcHashMap odds_graph;
} DclContent;

typedef struct dcl_sentences {
    int size;
    owner char** array;
} DclSentences;

typedef struct dcl_odds_value {
    float factor;
    int required;
} DclOddsValue;

typedef struct dcl_odds {
    borrow DclContent* content;
    owner DclOddsValue** graph;
} DclOdds;

typedef struct dcl_gen_input {
    borrow const char** target_keys;
    int target_keys_size;
    int target_sentences_size;

    borrow const char** dep_keys;
    int dep_keys_size;
    int min_dep_sentences;
} DclGenInput;

c_err dcl_content_init(DclContent* content, int alphabet_size, int keys_size);
c_err dcl_content_gen(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input);
void dcl_content_free(DclContent* content);
void dcl_sentences_free(void* sentences);

bool dcl_content_alphabet_contains_key(const DclContent* content, const char* key);
c_err dcl_content_alphabet_set_key(DclContent* content, const char* key);
c_err dcl_content_alphabet_add_sentence(DclContent* content, const char* key, const char* sentence);
c_err dcl_content_alphabet_borrow_sentences(const DclContent* content, const char* key, borrow DclSentences* sentences);

bool dcl_content_graph_contains_target_key(const DclContent* content, const char* target_key);
c_err dcl_content_graph_set_target_key(DclContent* content, const char* target_key);
bool dcl_content_graph_contains_dep_key(const DclContent* content, const char* target_key, const char* dep_key);
c_err dcl_content_graph_set_dep_key(DclContent* content, const char* target_key, const char* dep_key);
c_err dcl_content_graph_borrow_odds(const DclContent* content, const char* target_key, const char* dep_key, borrow DclOdds* odds);
c_err dcl_content_graph_set_odds(DclContent* content, const char* target_key, const char* dep_key, int index1, int index2, float factor, int required);

#endif
