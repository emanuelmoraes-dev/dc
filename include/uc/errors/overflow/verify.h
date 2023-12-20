#ifndef UC_ERRORS_OVERFLOW_VERIFY_H_INCLUDED
#define UC_ERRORS_OVERFLOW_VERIFY_H_INCLUDED

#include "uc/errors/overflow.h"

#define UC_ERR_IS_OVERFLOW_LARGE_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) > (MAX_VALUE) - (x)))

#define UC_ERR_IS_OVERFLOW_SMALL_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) < (MIN_VALUE) - (x)))

#define UC_ERR_IS_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE) \
    (UC_ERR_IS_OVERFLOW_LARGE_ADD(a, x, MIN_VALUE, MAX_VALUE) || UC_ERR_IS_OVERFLOW_SMALL_ADD(a, x, MIN_VALUE, MAX_VALUE))

#define UC_ERR_CHECK_OVERFLOW_ADD(a, x, MIN_VALUE, MAX_VALUE, largeArg, smallArg) (\
    UC_ERR_IS_OVERFLOW_LARGE_ADD(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(largeArg) :\
    UC_ERR_IS_OVERFLOW_SMALL_ADD(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(smallArg) :\
    C_OK\
)

#define UC_ERR_IS_OVERFLOW_LARGE_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) < 0) && ((a) > (MAX_VALUE) + (x)))

#define UC_ERR_IS_OVERFLOW_SMALL_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (((x) > 0) && ((a) < (MIN_VALUE) + (x)))

#define UC_ERR_IS_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE) \
    (UC_ERR_IS_OVERFLOW_LARGE_SUB(a, x, MIN_VALUE, MAX_VALUE) || UC_ERR_IS_OVERFLOW_SMALL_SUB(a, x, MIN_VALUE, MAX_VALUE))

#define UC_ERR_CHECK_OVERFLOW_SUB(a, x, MIN_VALUE, MAX_VALUE, largeArg, smallArg) (\
    UC_ERR_IS_OVERFLOW_LARGE_SUB(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(largeArg) :\
    UC_ERR_IS_OVERFLOW_SMALL_SUB(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(smallArg) :\
    C_OK\
)

#define __UC_ERR_IS_OVERFLOW_LARGE_POS_MULT(a_positive, x_positive, MIN_VALUE, MAX_VALUE) \
    ((x_positive) && (a_positive) > (MAX_VALUE) / (x_positive))

#define __UC_ERR_IS_OVERFLOW_LARGE_NEG_MULT(a_negative, x_negative, MIN_VALUE, MAX_VALUE) \
    ((a_negative) < (MAX_VALUE) / (x_negative))

#define __UC_ERR_IS_OVERFLOW_SMALL_NEG_POS_MULT(a_negative, x_positive, MIN_VALUE, MAX_VALUE) \
    ((x_positive) && (a_negative) < (MIN_VALUE) / (x_positive))

#define __UC_ERR_MULT_IS_NEGATIVE(a, x) (\
    ((a) < 0 && (x) > 0) ||\
    ((a) > 0 && (x) < 0)\
)

#define __UC_ERR_MULT_GET_NEGATIVE(a, x) \
    ((a) < 0 ? (a) : (x))

#define __UC_ERR_MULT_GET_POSITIVE(a, x) \
    ((a) > 0 ? (a) : (x))

#define UC_ERR_IS_OVERFLOW_LARGE_MULT(a, x, MIN_VALUE, MAX_VALUE) (\
    (\
        ((a) > 0 && (x) > 0) &&\
        __UC_ERR_IS_OVERFLOW_LARGE_POS_MULT(a, x, MIN_VALUE, MAX_VALUE)\
    ) || (\
        ((a) < 0 && (x) < 0) &&\
        __UC_ERR_IS_OVERFLOW_LARGE_NEG_MULT(a, x, MIN_VALUE, MAX_VALUE)\
    )\
)

#define UC_ERR_IS_OVERFLOW_SMALL_MULT(a, x, MIN_VALUE, MAX_VALUE) (\
    __UC_ERR_MULT_IS_NEGATIVE(a, x) &&\
    __UC_ERR_IS_OVERFLOW_SMALL_NEG_POS_MULT(\
        __UC_ERR_MULT_GET_NEGATIVE(a, x),\
        __UC_ERR_MULT_GET_POSITIVE(a, x),\
        MIN_VALUE,\
        MAX_VALUE\
    )\
)

#define UC_ERR_IS_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE) \
	(UC_ERR_IS_OVERFLOW_LARGE_MULT(a, x, MIN_VALUE, MAX_VALUE) || UC_ERR_IS_OVERFLOW_SMALL_MULT(a, x, MIN_VALUE, MAX_VALUE))

#define UC_ERR_CHECK_OVERFLOW_MULT(a, x, MIN_VALUE, MAX_VALUE, largeArg, smallArg) (\
    UC_ERR_IS_OVERFLOW_LARGE_MULT(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(largeArg) :\
    UC_ERR_IS_OVERFLOW_SMALL_MULT(a, x, MIN_VALUE, MAX_VALUE) ? UC_ERR_THROW_OVERFLOW(smallArg) :\
    C_OK\
)

#endif
