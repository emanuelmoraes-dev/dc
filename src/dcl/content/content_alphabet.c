#include "dcl/content.h"

c_err content_set_sentence(Content* content, move char* sentence, int index) {
    if (index < 0 || index >= content->alphabet_size) {
        return DCL_ERR_THROW_INDEX_OUT(DCL_ERR_ARG_INDEX_OUT_ALPHABET);
    }

    content->alphabet[index] = sentence;

    return C_OK;
}
