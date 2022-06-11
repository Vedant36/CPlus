/* Source: https://boards.4channel.org/g/thread/86586328#p86590507 */
#include <stdio.h>
#include <stdlib.h>

#define LOCAL_COUNTER_INIT enum { COUNTER_BASE = __COUNTER__ }
#define LOCAL_COUNTER (__COUNTER__ - COUNTER_BASE)

#define error_enable    \
    LOCAL_COUNTER_INIT; \
    int err = -1;       \
    exit_error:         \
    switch (err) {      \
    case -1:

#define error_handler    \
    if (0) {             \
        goto exit_error; \
    case LOCAL_COUNTER:

#define error_return(val) \
    default:              \
    return (val);     \
    }

#define end          \
    err -= 2;        \
    goto exit_error; \
    }

#define throw_error          \
    err = LOCAL_COUNTER - 1; \
    goto exit_error

int func(void)
{
    error_enable;

    void* x = malloc(1);

    if (x == NULL) {
        printf("Failed to allocate x\n");
        throw_error;
    }

    error_handler {
        printf("Freeing x\n");
        free(x);
    } end;

    void* y = malloc(-1);

    if (y == NULL) {
        printf("Failed to allocate y\n");
        throw_error;
    }

    error_handler {
        printf("Freeing y\n");
        free(y);
    } end;

    return 0;

    error_return(-1);
}

int main(void)
{
    int ret = func();
    printf("func returned %d\n", ret);
    return ret;
}

