#include <stdio.h>
#include <limits.h>
#include "dcl/content.h"

c_err foo(int argc, const char* argv[]);
int main(int argc, const char* argv[]) {
    c_err error = foo(argc, argv);

    if (error != C_OK) {
        fprintf(stderr, "!> Error (code %d). ", error);
        int error_len = dcl_err_strlen(error);
        char message[error_len + 1];
        dcl_err_strcpy_s(error, message, error_len + 1);
        fprintf(stderr, "%s\n", message);
        return error;
    }

    return 0;
}

c_err foo_alphabet_keys(DclContent* content, const char* keys[], int keys_size);
c_err foo_alphabet_sentences(DclContent* content, const char* key, const char* sentences[], int sentences_size);
c_err foo_graph_keys(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size);
c_err foo_graph_odds(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size, int index1, int index2, float factor, int required);
c_err foo(int argc, const char* argv[]) {
    int alphabet_size = 10;
    int keys_size = 2;

    DclContent content;
    c_err error = dcl_content_init(&content, alphabet_size, keys_size);
    if (error != C_OK) {
        fprintf(stderr, "dcl_content_init error %d\n", error);
        return error;
    }

    puts("$> allocating alphabet keys...");

    const char creatures_key[] = "creatures";
    const char itens_key[] = "itens";
    const char* keys[] = {creatures_key, itens_key};
    error = foo_alphabet_keys(&content, keys, 2);
    if (error != C_OK) {
        fprintf(stderr, "foo_alphabet_keys error %d\n", error);
        dcl_sentences_free(&content);
        return error;
    }

    puts("$> allocating alphabet sentences...");

    int creatures_size = 2;
    const char human[] = "human";
    const char ogre[] = "ogre";
    const char* creatures_sentences[] = {human, ogre};
    error = foo_alphabet_sentences(&content, creatures_key, creatures_sentences, creatures_size);
    if (error != C_OK) {
        fprintf(stderr, "foo_alphabet_sentences (1) error %d\n", error);
        dcl_content_free(&content);
        return error;
    }

    int itens_size = 3;
    const char shield[] = "shield";
    const char sword[] = "sword";
    const char ax[] = "ax";
    const char* itens_sentences[] = {shield, sword, ax};
    error = foo_alphabet_sentences(&content, itens_key, itens_sentences, itens_size);
    if (error != C_OK) {
        fprintf(stderr, "foo_alphabet_sentences (2) error %d\n", error);
        dcl_content_free(&content);
        return error;
    }

    puts("$> allocating graph keys...");

    int creatures_dep_keys_size = 1;
    const char* creatures_dep_keys[] = {itens_key};
    error = foo_graph_keys(&content, creatures_key, creatures_dep_keys, creatures_dep_keys_size);
    if (error != C_OK) {
        fprintf(stderr, "foo_graph_keys error %d\n", error);
        dcl_content_free(&content);
        return error;
    }

    puts("$> allocating graph values...");

    for (int i = 0; i < creatures_size; ++i) {
        for (int j = 0; j < itens_size; ++j) {
            error = foo_graph_odds(&content, creatures_key, creatures_dep_keys, creatures_dep_keys_size, i, j, 0.5, 0);
            if (error != C_OK) {
                fprintf(stderr, "foo_graph_odds error %d\n", error);
                dcl_content_free(&content);
                return error;
            }
        }
    }

    puts("$> generating parameters...");

    int target_keys_size = 1;
    const char* target_keys[] = {creatures_key};

    DclGenInput gen;
    gen.target_keys = target_keys;
    gen.target_keys_size = target_keys_size;
    gen.target_sentences_size = 2;

    gen.dep_keys = creatures_dep_keys;
    gen.dep_keys_size = creatures_dep_keys_size;
    gen.min_dep_sentences = 2;

    puts("$> allocating result memory...");

    UcHashMap dcl_sentences_result;
    error = uc_hash_map_init(&dcl_sentences_result, DCL_HASH_MAP_CAPACITY(target_keys_size, INT_MAX));
    if (error != C_OK) {
        fprintf(stderr, "uc_hash_map_init error %d\n", error);
        dcl_content_free(&content);
        return error;
    }

    puts("$> generating results...");

    error = dcl_content_gen(&content, &dcl_sentences_result, &gen);
    if (error != C_OK) {
        fprintf(stderr, "dcl_content_gen error %d\n", error);
        uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
        dcl_content_free(&content);
        return error;
    }

    puts("$> printing result...");

    UcHashMapIterator it;
    uc_hash_map_make_iterator(&dcl_sentences_result, &it);
    while(uc_hash_map_has_next(&dcl_sentences_result, &it)) {
        error = uc_hash_map_next(&dcl_sentences_result, &it);
        if (error != C_OK) {
            fprintf(stderr, "uc_hash_map_next error %d\n", error);
            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return error;
        }

        char* target_key = NULL;
        DclSentences* sentences = NULL;
        error = uc_hash_map_borrow_key_value(&dcl_sentences_result, &it, &target_key, (void*) &sentences);
        if (error != C_OK) {
            fprintf(stderr, "uc_hash_map_borrow_key_value error %d\n", error);
            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return error;
        }

        if (target_key == NULL) {
            fprintf(stderr, "target_key NULL\n");
            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_RESULT_KEY);
        }

        if (sentences == NULL || sentences->array == NULL) {
            fprintf(stderr, "sentences NULL\n");
            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_RESULT_SENTENCES);
        }

        for (int i = 0; i < sentences->size; ++i) {
            const char* sentence = sentences->array[i];
            if (sentence == NULL) {
                fprintf(stderr, "sentence NULL\n");
                uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
                dcl_content_free(&content);
                return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_RESULT_SENTENCE);
            }
            printf("#> %s: %s", target_key, sentence);
        }

        if (sentences->size > 0) {
            printf("\n");
        }
    }

    puts("$> clearing memory...");

    uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
    dcl_content_free(&content);

    puts("$> done!");
    return C_OK;
}

c_err foo_alphabet_keys(DclContent* content, const char* keys[], int keys_size) {
    for (int i = 0; i < keys_size; ++i) {
        printf("$>> allocating alphabet key \"%s\"...\n", keys[i]);
        c_err error = dcl_content_alphabet_set_key(content, keys[i]);
        if (error != C_OK) {
            return error;
        }
        printf("$>> alphabet key \"%s\" allocated\n", keys[i]);
    }
    return C_OK;
}

c_err foo_alphabet_sentences(DclContent* content, const char* key, const char* sentences[], int sentences_size) {
    for (int i = 0; i < sentences_size; ++i) {
        printf("$>> allocating alphabet sentence \"%s\" mapped by \"%s\"...\n", sentences[i], key);
        c_err error = dcl_content_alphabet_add_sentence(content, key, sentences[i]);
        if (error != C_OK) {
            return error;
        }
        printf("$>> alphabet sentence \"%s\" mapped by \"%s\" allocated\n", sentences[i], key);
    }
    return C_OK;
}

c_err foo_graph_keys(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size) {
    printf("$>> allocating graph target key \"%s\"...\n", target_key);
    c_err error = dcl_content_graph_set_target_key(content, target_key);
    if (error != C_OK) {
        return error;
    }
    printf("$>> graph target key \"%s\" allocated\n", target_key);

    for (int i = 0; i < dep_keys_size; ++i) {
        printf("$>> allocating graph dep key \"%s\" mapped by \"%s\"...\n", dep_keys[i], target_key);
        error = dcl_content_graph_set_dep_key(content, target_key, dep_keys[i]);
        if (error != C_OK) {
            return error;
        }
        printf("$>> graph dep key \"%s\" mapped by \"%s\" allocated\n", dep_keys[i], target_key);
    }

    return C_OK;
}

c_err foo_graph_odds(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size, int index1, int index2, float factor, int required) {
    for (int i = 0; i < dep_keys_size; ++i) {
        printf("$>> allocating graph odds (%.2f:%d) mapped by [%s][%s]...\n", factor, required, target_key, dep_keys[i]);
        c_err error = dcl_content_graph_set_odds(content, target_key, dep_keys[i], index1, index2, factor, required);
        if (error != C_OK) {
            return error;
        }
        printf("$>> graph odds (%.2f:%d) mapped by [%s][%s] allocated\n", factor, required, target_key, dep_keys[i]);
    }
    return C_OK;
}
