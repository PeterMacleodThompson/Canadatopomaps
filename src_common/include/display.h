/**
 * DOC: -- display.h -- display layout parameters
 * Peter Thompson Nov 2019
 * 
 */
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_ttf.h>

#define TRUE 1
#define FALSE 0
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

/* global variables for display declared in SDL2init.c */
extern SDL_Window *globalwindow;     /* The window we'll be rendering to */
extern SDL_Renderer *globalrenderer; /* The window renderer */
extern SDL_Texture *globaltexture;   /* texture for display window */

/* global path for images, maps */
extern char *globaldatapath;







