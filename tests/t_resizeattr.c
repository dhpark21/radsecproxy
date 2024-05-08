/* Copyright (C) 2019, SWITCH */
/* See LICENSE for licensing information. */

#include "../rewrite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_resize(int start_size, int target_size, uint8_t shouldfail) {

    uint8_t *value = malloc(start_size);
    struct tlv *attr;
    int result = 1;

    memset(value, 42, start_size);
    attr = maketlv(1, start_size, value);

    if (!resizeattr(attr, target_size))
        result = shouldfail;
    else if (shouldfail)
        result = 0;
    else if (attr->l != target_size)
        result = 0;
    else if (memcmp(attr->v, value, target_size <= start_size ? target_size : start_size))
        result = 0;

    freetlv(attr);
    free(value);
    return result;
}

int main(int argc, char *argv[]) {
    int testcount = 4;

    printf("1..%d\n", testcount);
    testcount = 1;

    /* test resizeattr normal */
    if (!test_resize(4, 8, 0))
        printf("not ");
    printf("ok %d - resizeattr\n", testcount++);

    /* test resizeattr to 0 */
    if (!test_resize(4, 0, 0))
        printf("not ");
    printf("ok %d - resizeattr to zero\n", testcount++);

    /* test resizeattr to max size */
    if (!test_resize(128, 253, 0))
        printf("not ");
    printf("ok %d - resizeattr to max size\n", testcount++);

    /* test resizeattr to oversize */
    if (!test_resize(128, 254, 1))
        printf("not ");
    printf("ok %d - resizeattr to oversize\n", testcount++);

    return 0;
}
