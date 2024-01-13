#include "dcl/content.h"
#include "uc/math_util.h"
#include <stdlib.h>

bool dcl_content_alphabet_contains_key(const DclContent* content, const char* key) {
	if (key == NULL) {
		return false;
	}

	return uc_hash_map_contains(&content->alphabet, key);
}

c_err dcl_content_alphabet_set_key(DclContent* content, const char* key) {
	if (key == NULL) {
		return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (dcl_content_alphabet_contains_key(content, key)) {
		return C_OK;
	}

	DclSentences* sentences = (DclSentences*) malloc(sizeof(DclSentences));

	if (sentences == NULL) {
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	sentences->size = 0;
	sentences->array = (char**) malloc(sizeof(char*) * content->alphabet_size);

	if (sentences->array == NULL) {
		free(sentences);
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	char* new_key = _strdup(key);

	if (new_key == NULL) {
		free(sentences->array);
		free(sentences);
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_ALPHABET_KEY);
	}

	c_err error = uc_hash_map_insert(&content->alphabet, new_key, sentences);

	if (error != C_OK) {
		free(sentences->array);
		free(sentences);
		free(new_key);
	}

	return error;
}

c_err dcl_content_alphabet_add_sentence(DclContent* content, const char* key, const char* sentence) {
	if (key == NULL) {
		return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (sentence == NULL) {
		return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_SENTENCE);
	}

	if (!dcl_content_alphabet_contains_key(content, key)) {
		return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
	}

	DclSentences* sentences = (DclSentences*) uc_hash_map_get(&content->alphabet, key);

	if (sentences == NULL || sentences->array == NULL) {
		return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES);
	}

	int new_size = MAX(1, sentences->size + 1);

	if (new_size < 0 || new_size > content->alphabet_size) {
		return dcl_err_throw_index_out(DCL_ERR_ARG_INDEX_OUT_ALPHABET);
	}

	sentences->array[new_size - 1] = _strdup(sentence);

	if (sentences->array[new_size - 1] == NULL) {
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	sentences->size = new_size;

	return C_OK;
}

c_err dcl_content_alphabet_borrow_sentences(const DclContent* content, const char* key, borrow DclSentences* sentences) {
	if (key == NULL) {
		return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (!dcl_content_alphabet_contains_key(content, key)) {
		return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
	}

	DclSentences* item = (DclSentences*) uc_hash_map_get(&content->alphabet, key);

	if (item == NULL) {
		return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES);
	}

	*sentences = *item;

	return C_OK;
}
