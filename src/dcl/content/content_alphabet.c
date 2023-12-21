#include "dcl/content.h"
#include "uc/math_util.h"
#include <stdlib.h>

bool content_alphabet_contains_key(const Content* content, const char* key) {
	if (key == NULL) {
		return false;
	}

	return hash_map_contains(&content->alphabet, key);
}

c_err content_alphabet_set_key(Content* content, move char* key) {
	if (key == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (content_alphabet_contains_key(content, key)) {
		free(key);
		return C_OK;
	}

	Sentences* sentences = (Sentences*) malloc(sizeof(Sentences));

	if (sentences == NULL) {
		free(key);
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	sentences->size = 0;
	sentences->list = (char**) malloc(sizeof(char*) * content->alphabet_size);

	if (sentences->list == NULL) {
		free(sentences);
		free(key);
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	c_err error = hash_map_insert(&content->alphabet, key, sentences);

	if (error != C_OK && !hash_map_contains(&content->alphabet, key)) {
		free(sentences->list);
		free(sentences);
		free(key);
	}

	return error;
}

c_err content_alphabet_add_sentence(Content* content, const char* key, move char* sentence) {
	if (key == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (sentence == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_ALPHABET_SENTENCE);
	}

	if (!content_alphabet_contains_key(content, key)) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
	}

	Sentences* sentences = (Sentences*) hash_map_get(&content->alphabet, key);

	if (sentences == NULL || sentences->list == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES);
	}

	int new_size = MAX(1, sentences->size + 1);

	if (new_size < 0 || new_size > content->alphabet_size) {
		return DCL_ERR_THROW_INDEX_OUT(DCL_ERR_ARG_INDEX_OUT_ALPHABET);
	}

	sentences->list[new_size] = sentence;
	sentences->size = new_size;

	return C_OK;
}

c_err content_alphabet_borrow_sentences(const Content* content, const char* key, borrow Sentences* sentences) {
	if (key == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_ALPHABET_KEY);
	}

	if (!content_alphabet_contains_key(content, key)) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
	}

	Sentences* item = (Sentences*) hash_map_get(&content->alphabet, key);

	if (item == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES);
	}

	*sentences = *item;

	return C_OK;
}
