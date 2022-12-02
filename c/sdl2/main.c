#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "util.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640
#define FPS 60

int main(int argc, char **argv)
{
	/* initialization */
	(void) argc;
	(void) argv;
	scc(SDL_Init(SDL_INIT_VIDEO));
	atexit(SDL_Quit);
	SDL_Window  *window  = SDL_CreateWindow("Windows 9",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			0);
	SDL_Surface *surface = scp(SDL_GetWindowSurface(window));

	/* loading image */
	SDL_Surface *image = scp(IMG_Load("painting.bmp"));
	SDL_ConvertSurface(image, surface->format, 0);
	scc((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) - 1);
	atexit(IMG_Quit);
	SDL_Rect r = image->clip_rect;

	r.x = (surface->w - image->w) / 2;
	r.y = (surface->h - image->h) / 2;
	int mousex, mousey;
	const int accel = 10;
	float zoom = 1, zfact = 0.01,
	      zmax = MIN((float) surface->w / image->w,
			 (float) surface->h / image->h);
	bool running = true;
	SDL_Event event;
	while (running) {
		const Uint32 start = SDL_GetTicks();
		SDL_GetMouseState(&mousex, &mousey);
		zoom = MIN(zoom, zmax);
		r.w =  MIN(image->w * zoom, surface->w);
		r.h =  MIN(image->h * zoom, surface->h);
		r.x += (mousex - r.x - r.w / 2) / accel;
		r.y += (mousey - r.y - r.h / 2) / accel;
		r.x =  CLIP(0, r.x, surface->w - r.w);
		r.y =  CLIP(0, r.y, surface->h - r.h);
		SDL_FillRect(surface, NULL, 0xff282d3e);
		SDL_BlitScaled(image, NULL, surface, &r);
		SDL_UpdateWindowSurface(window);

		while(SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				surface = SDL_GetWindowSurface(window);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_q:
					running = false;
					break;
				case SDLK_r:
					zoom = 1;
				}
				break;
			case SDL_MOUSEWHEEL:
				if (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
					zoom += zfact * event.wheel.y;
				else
					zoom -= zfact * event.wheel.y;
				break;
			/* default: */
			/* 	if (event.type != last) { */
			/* 		printf("%x.", event.type); */
			/* 		fflush(stdout); */
			/* 		last = event.type; */
			/* 	} */
			}
		}

		const Uint32 delta_time_ms = 1000 / FPS;
		const Uint32 time_passed = SDL_GetTicks() - start;
		printf("\r%d", 1000 / time_passed);
		fflush(stdout);
		if (time_passed < delta_time_ms)
			SDL_Delay(delta_time_ms - time_passed);
	}

	SDL_FreeSurface(image);
	SDL_DestroyWindow(window);
	return 0;
}

// vim: complete+=sSDLkeywords
