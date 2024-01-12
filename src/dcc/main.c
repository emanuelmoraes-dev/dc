#include <limits.h>
#include <stdio.h>
#include "dcc/logs.h"
#include "dcl/content.h"

c_err foo(int argc, const char* argv[]);
int main(int argc, const char* argv[]) {
    c_err error = foo(argc, argv);

    if (error != C_OK) {
        int error_len = dcl_err_strlen(error);
        char error_message[error_len + 1];
        dcl_err_strcpy_s(error, error_message, sizeof(error_message));

        UC_LOG_BUFFER(logs, format, "Error: %s. Code %d.", error_len + 10);
        uc_log_format(logs, sizeof(logs), format, error_message, error);
        LOG(ERR, logs);

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
        UC_LOG_BUFFER(logs, format, "dcl_content_init error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        return error;
    }

    LOG(INFO, "$> allocating alphabet keys...");

    const char creatures_key[] = "creatures";
    const char itens_key[] = "itens";
    const char* keys[] = {creatures_key, itens_key};
    error = foo_alphabet_keys(&content, keys, 2);
    if (error != C_OK) {
        UC_LOG_BUFFER(logs, format, "foo_alphabet_keys error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        dcl_sentences_free(&content);
        return error;
    }

    LOG(INFO, "$> allocating alphabet sentences...");

    int creatures_size = 2;
    const char human[] = "human";
    const char ogre[] = "ogre";
    const char* creatures_sentences[] = {human, ogre};
    error = foo_alphabet_sentences(&content, creatures_key, creatures_sentences, creatures_size);
    if (error != C_OK) {
        UC_LOG_BUFFER(logs, format, "foo_alphabet_sentences (1) error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

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
        UC_LOG_BUFFER(logs, format, "foo_alphabet_sentences (2) error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        dcl_content_free(&content);
        return error;
    }

    LOG(INFO, "$> allocating graph keys...");

    int creatures_dep_keys_size = 1;
    const char* creatures_dep_keys[] = {itens_key};
    error = foo_graph_keys(&content, creatures_key, creatures_dep_keys, creatures_dep_keys_size);
    if (error != C_OK) {
        UC_LOG_BUFFER(logs, format, "foo_graph_keys error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        dcl_content_free(&content);
        return error;
    }

    LOG(INFO, "$> allocating graph values...");

    for (int i = 0; i < creatures_size; ++i) {
        for (int j = 0; j < itens_size; ++j) {
            error = foo_graph_odds(&content, creatures_key, creatures_dep_keys, creatures_dep_keys_size, i, j, 0.5, 0);
            if (error != C_OK) {
                UC_LOG_BUFFER(logs, format, "foo_graph_odds error %d", 10);
                uc_log_format(logs, sizeof(logs), format, error);
                LOG(ERR, logs);

                dcl_content_free(&content);
                return error;
            }
        }
    }

    LOG(INFO, "$> generating parameters...");

    int target_keys_size = 1;
    const char* target_keys[] = {creatures_key};

    DclGenInput gen;
    gen.target_keys = target_keys;
    gen.target_keys_size = target_keys_size;
    gen.target_sentences_size = 2;

    gen.dep_keys = creatures_dep_keys;
    gen.dep_keys_size = creatures_dep_keys_size;
    gen.min_dep_sentences = 2;

    LOG(INFO, "$> allocating result memory...");

    UcHashMap dcl_sentences_result;
    error = uc_hash_map_init(&dcl_sentences_result, DCL_HASH_MAP_CAPACITY(target_keys_size, INT_MAX));
    if (error != C_OK) {
        UC_LOG_BUFFER(logs, format, "uc_hash_map_init error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        dcl_content_free(&content);
        return error;
    }

    LOG(INFO, "$> generating results...");

    error = dcl_content_gen(&content, &dcl_sentences_result, &gen);
    if (error != C_OK) {
        UC_LOG_BUFFER(logs, format, "dcl_content_gen error %d", 10);
        uc_log_format(logs, sizeof(logs), format, error);
        LOG(ERR, logs);

        uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
        dcl_content_free(&content);
        return error;
    }

    LOG(INFO, "$> printing result...");

    UcHashMapIterator it;
    uc_hash_map_make_iterator(&dcl_sentences_result, &it);
    while(uc_hash_map_has_next(&dcl_sentences_result, &it)) {
        error = uc_hash_map_next(&dcl_sentences_result, &it);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs, format, "uc_hash_map_next error %d", 10);
            uc_log_format(logs, sizeof(logs), format, error);
            LOG(ERR, logs);

            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return error;
        }

        char* target_key = NULL;
        DclSentences* sentences = NULL;
        error = uc_hash_map_borrow_key_value(&dcl_sentences_result, &it, &target_key, (void*) &sentences);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs, format, "uc_hash_map_borrow_key_value error %d", 10);
            uc_log_format(logs, sizeof(logs), format, error);
            LOG(ERR, logs);

            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return error;
        }

        if (target_key == NULL) {
            LOG(ERR, "target_key NULL");

            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_RESULT_KEY);
        }

        if (sentences == NULL || sentences->array == NULL) {
            LOG(ERR, "sentences NULL");

            uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
            dcl_content_free(&content);
            return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_RESULT_SENTENCES);
        }

        for (int i = 0; i < sentences->size; ++i) {
            const char* sentence = sentences->array[i];
            if (sentence == NULL) {
                LOG(ERR, "sentence NULL");

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

    LOG(INFO, "$> clearing memory...");

    uc_hash_map_free(&dcl_sentences_result, dcl_sentences_free);
    dcl_content_free(&content);

    printf("$> done!\n");
    return C_OK;
}

c_err foo_alphabet_keys(DclContent* content, const char* keys[], int keys_size) {
    for (int i = 0; i < keys_size; ++i) {
        const char* key = keys[i];
        unsigned long long key_len = strlen(key);

        UC_LOG_BUFFER(logs1, format1, "$>> allocating alphabet key \"%s\"...", key_len);
        uc_log_format(logs1, sizeof(logs1), format1, key);
        LOG(INFO, logs1);

        c_err error = dcl_content_alphabet_set_key(content, keys[i]);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs_err, format_err, "dcl_content_alphabet_set_key error %d", 10);
            uc_log_format(logs_err, sizeof(logs_err), format_err, error);
            LOG(ERR, logs_err);

            return error;
        }

        UC_LOG_BUFFER(logs2, format2, "$>> alphabet key \"%s\" allocated", key_len);
        uc_log_format(logs2, sizeof(logs2), format2, key);
        LOG(INFO, logs2);
    }
    return C_OK;
}

c_err foo_alphabet_sentences(DclContent* content, const char* key, const char* sentences[], int sentences_size) {
    unsigned long long key_len = strlen(key);
    for (int i = 0; i < sentences_size; ++i) {
        const char* sentence = sentences[i];
        unsigned long long sentence_len = strlen(sentence);

        UC_LOG_BUFFER(logs1, format1, "$>> allocating alphabet sentence \"%s\" mapped by \"%s\"...", sentence_len + key_len);
        uc_log_format(logs1, sizeof(logs1), format1, sentence, key);
        LOG(INFO, logs1);

        c_err error = dcl_content_alphabet_add_sentence(content, key, sentence);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs_err, format_err, "dcl_content_alphabet_add_sentence error %d", 10);
            uc_log_format(logs_err, sizeof(logs_err), format_err, error);
            LOG(ERR, logs_err);

            return error;
        }

        UC_LOG_BUFFER(logs2, format2, "$>> alphabet sentence \"%s\" mapped by \"%s\" allocated", sentence_len + key_len);
        uc_log_format(logs2, sizeof(logs2), format2, sentence, key);
        LOG(INFO, logs2);
    }
    return C_OK;
}

c_err foo_graph_keys(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size) {
    unsigned long long target_key_len = strlen(target_key);
    UC_LOG_BUFFER(logs1, format1, "$>> allocating graph target key \"%s\"...", target_key_len);
    uc_log_format(logs1, sizeof(logs1), format1, target_key);
    LOG(INFO, logs1);

    c_err error = dcl_content_graph_set_target_key(content, target_key);
    if (error != C_OK) {
        UC_LOG_BUFFER(logs_err, format_err, "dcl_content_graph_set_target_key error %d", 10);
        uc_log_format(logs_err, sizeof(logs_err), format_err, error);
        LOG(ERR, logs_err);

        return error;
    }

    UC_LOG_BUFFER(logs2, format2, "$>> graph target key \"%s\" allocated", target_key_len);
    uc_log_format(logs2, sizeof(logs2), format2, target_key);
    LOG(INFO, logs2);

    for (int i = 0; i < dep_keys_size; ++i) {
        const char* dep_key = dep_keys[i];
        unsigned long long dep_key_len = strlen(dep_key);

        UC_LOG_BUFFER(logs3, format3, "$>> allocating graph dep key \"%s\" mapped by \"%s\"...", dep_key_len + target_key_len);
        uc_log_format(logs3, sizeof(logs3), format3, dep_key, target_key);
        LOG(INFO, logs3);

        error = dcl_content_graph_set_dep_key(content, target_key, dep_keys[i]);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs_err, format_err, "dcl_content_graph_set_dep_key error %d", 10);
            uc_log_format(logs_err, sizeof(logs_err), format_err, error);
            LOG(ERR, logs_err);

            return error;
        }

        UC_LOG_BUFFER(logs4, format4, "$>> graph dep key \"%s\" mapped by \"%s\" allocated", dep_key_len + target_key_len);
        uc_log_format(logs4, sizeof(logs4), format4, dep_key, target_key);
        LOG(INFO, logs4);
    }

    return C_OK;
}

c_err foo_graph_odds(DclContent* content, const char* target_key, const char* dep_keys[], int dep_keys_size, int index1, int index2, float factor, int required) {
    unsigned long long target_key_len = strlen(target_key);

    for (int i = 0; i < dep_keys_size; ++i) {
        const char* dep_key = dep_keys[i];
        unsigned long long dep_key_len = strlen(dep_key);

        UC_LOG_BUFFER(logs1, format1, "$>> allocating graph odds (%.2f:%d) mapped by [%s][%s]...", 15 + 10 + target_key_len + dep_key_len);
        uc_log_format(logs1, sizeof(logs1), format1, factor, required, target_key, dep_key);
        LOG(INFO, logs1);

        c_err error = dcl_content_graph_set_odds(content, target_key, dep_keys[i], index1, index2, factor, required);
        if (error != C_OK) {
            UC_LOG_BUFFER(logs_err, format_err, "dcl_content_graph_set_odds error %d", 10);
            uc_log_format(logs_err, sizeof(logs_err), format_err, error);
            LOG(ERR, logs_err);

            return error;
        }

        UC_LOG_BUFFER(logs2, format2, "$>> graph odds (%.2f:%d) mapped by [%s][%s] allocated", 15 + 10 + target_key_len + dep_key_len);
        uc_log_format(logs2, sizeof(logs2), format2, factor, required, target_key, dep_key);
        LOG(INFO, logs2);
    }
    return C_OK;
}
