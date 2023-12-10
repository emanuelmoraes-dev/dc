#include "dc/lib/content.h"

c_err content_set_odds(Content* content, int si1, int si2, float odds) {
	if (si1 < 0 || si2 < 0 || si1 >= content->alphabet_size || si2 >= content->alphabet_size) {
		return DC_LIB_ERR_THROW_INDEX_OUT(DC_LIB_ERR_ARG_INDEX_OUT_ODDS);
	}

	content->odds_graph[si1][si2] = odds;

	return DC_LIB_OK;
}
