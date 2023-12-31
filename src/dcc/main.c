#include <stdio.h>
#include "dcl/content.h"

c_err foo(int argc, const char* argv[]);
int main(int argc, const char* argv[]) {
    c_err error = foo(argc, argv);

    if (error != C_OK) {
        int error_len = dcl_err_strlen(error);
        char message[error_len + 1];
        dcl_err_strcpy_s(error, message, error_len + 1);
        fprintf(stderr, "Error: %s. Code %d\n", message, error);
        return error;
    }

    return 0;
}

c_err foo_alphabet_keys(DclContent* content, const char* keys[], int keys_size);
c_err foo_alphabet_sentences(DclContent* content, const char* key, const char* sentences[], int sentences_size);
c_err foo(int argc, const char* argv[]) {
    int alphabet_size = 10;
    int keys_size = 2;

    DclContent content;
    c_err error = dcl_content_init(&content, alphabet_size, keys_size);
    if (error != C_OK) {
        return error;
    }

    const char creatures_key[] = "creatures";
    const char itens_key[] = "itens";
    const char* keys[] = {creatures_key, itens_key};
    error = foo_alphabet_keys(&content, keys, 2);
    if (error != C_OK) {
        dcl_sentences_free(&content);
        return error;
    }

    const char human[] = "human";
    const char ogre[] = "ogre";
    const char* creatures_sentences[] = {human, ogre};
    error = foo_alphabet_sentences(&content, creatures_key, creatures_sentences, 2);
    if (error != C_OK) {
        dcl_content_free(&content);
        return error;
    }

    const char shield[] = "shield";
    const char sword[] = "sword";
    const char ax[] = "ax";
    const char* itens_sentences[] = {shield, sword, ax};
    error = foo_alphabet_sentences(&content, itens_key, itens_sentences, 3);
    if (error != C_OK) {
        dcl_content_free(&content);
        return error;
    }

    return C_OK;
}

c_err foo_alphabet_keys(DclContent* content, const char* keys[], int keys_size) {
    for (int i = 0; i < keys_size; ++i) {
        c_err error = dcl_content_alphabet_set_key(content, keys[i]);
        if (error != C_OK) {
            return error;
        }
    }
    return C_OK;
}

c_err foo_alphabet_sentences(DclContent* content, const char* key, const char* sentences[], int sentences_size) {
    for (int i = 0; i < sentences_size; ++i) {
        c_err error = dcl_content_alphabet_add_sentence(content, key, sentences[i]);
        if (error != C_OK) {
            return error;
        }
    }
    return C_OK;
}
