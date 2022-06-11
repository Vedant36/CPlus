#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "util.h"
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	scc(SDL_Init(SDL_INIT_VIDEO));
	atexit(SDL_Quit);
	SDL_Window  *window  = SDL_CreateWindow("Windows 9",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			0);
	SDL_Surface *surface = scp(SDL_GetWindowSurface(window));

	int mousex, mousey;
	const int accel = 10;
	bool running = true;
	SDL_Event event;
	/* SDL_EventType last = SDL_FIRSTEVENT; */
	while (running) {
		/* const Uint32 start = SDL_GetTicks(); */

		while(SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_q:
					running = false;
					break;
				}
			/* default: */
			/* 	if (event.type != last) { */
			/* 		printf("%x.", event.type); */
			/* 		fflush(stdout); */
			/* 		last = event.type; */
			/* 	} */
			}
		}

		/* const Uint32 delta_time_ms = 1000 / FPS; */
		/* const Uint32 time_passed = SDL_GetTicks() - start; */
		/* printf("\r%d", 1000 / time_passed); */
		/* fflush(stdout); */
		/* if (time_passed < delta_time_ms) */
		/* 	SDL_Delay(delta_time_ms - time_passed); */
	}

	SDL_DestroyWindow(window);
	return 0;
}

// vim: complete+=sSDLkeywords
