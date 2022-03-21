// Source: https://github.com/tsoding/ded/blob/master/src/sdl_extra.c
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
/* clips B between A and C */
#define CLIP(A, B, C) ((B) > (C) ? (C) : (B) < (A) ? (A) : (B))
#define UNHEX(color) \
	((color) >> (8 * 0)) & 0xFF, \
	((color) >> (8 * 1)) & 0xFF, \
	((color) >> (8 * 2)) & 0xFF, \
	((color) >> (8 * 3)) & 0xFF

// SDL Check Code
#define scc(code)	    \
{			    \
    if (code < 0) {	    \
        fprintf(stderr, "SDL ERROR:%d %s\n", __LINE__, SDL_GetError());	\
        exit(1);	    \
    }			    \
}

// SDL Check Pointer
inline void *scp(void *ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }

    return ptr;
}

