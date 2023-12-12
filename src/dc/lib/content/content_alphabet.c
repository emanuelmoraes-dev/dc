#include "dc/lib/content.h"

c_err content_set_sentence(Content* content, move char* sentence, int index) {
    if (index < 0 || index >= content->alphabet_size) {
        return DC_LIB_ERR_THROW_INDEX_OUT(DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET);
    }

    content->alphabet[index] = sentence;

    return C_OK;
}
