#include "dc/lib/content.h"

dc_lib_err content_set_sentence(Content* content, move char* sentence, int index) {
    if (index < 0 || index >= content->alphabet_size) {
        return DC_LIB_ERR_THROW_INDEX_OUT(DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET);
    }

    content->alphabet[index] = sentence;

    return DC_LIB_OK;
}
