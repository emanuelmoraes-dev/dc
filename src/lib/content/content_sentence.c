#include "dc/content.h"

dc_error content_add_sentence(Content* content, move char* sentence, int index) {
    if (index < 0 || index >= content->alphabet_size) {
        return DC_ERR_THROW_INDEX_OUT(DC_ERR_ARG_INDEX_OUT_ALPHABET);
    }

    content->alphabet[index] = sentence;

    return DC_OK;
}
