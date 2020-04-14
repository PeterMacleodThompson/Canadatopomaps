/**
 * DOC: --  initSDL2.c  -- Initialize display
 * Peter Thompson   -- 2015, revised 2019
 *
 * Initialize global variables
 *   - globalwindow   - what we see on display. Used only for opening/closing
 *   - globalrenderer - we use directfb - depends on linux proper setup!!
 *   - globaldatapath - to maps, images, sprites
 * FIXME new program init.c calls 
 *   initSDL2() find_datadir(), initcurl(),
 * FIXME new program getcountryusage() == new state  
 * FIXME add printfs to SDL2init from initdisplayhardware.c  
 */

#include "display.h"
#include <stdio.h>

/* GLOBAL VARIABLES FOR DISPLAY, datapath */
SDL_Window   *globalwindow;   /* Display window we'll be rendering to */
SDL_Renderer *globalrenderer; /* The window renderer */


/**
 * initSDL2() - initialize global variables and SDL2
 * Return: True or False depending on whether everything initialized ok
 */
int initSDL2() {

  int success = TRUE;

  /* informational & debugging variables */
  SDL_version compiled;
  SDL_version linked;
  SDL_RendererInfo info;
  int r, i;

  /* print machine video driver information */
  r = SDL_GetNumVideoDrivers();
  printf("Number of Video Drivers = %d\n", r);
  i = 0;
  while (i < r) {
    printf("  video driver %d = %s\n", i, SDL_GetVideoDriver(i));
    i++;
  }

  /* debug SDL2 with messages to stderr */
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
  SDL_Log("SDL log is verbose\n");

  /* Initialize SDL2 - video only */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = FALSE;
  } else
    printf("Current Video Driver = %s\n", SDL_GetCurrentVideoDriver());

  /* display SDL version. see https://wiki.libsdl.org/SDL_VERSION  */
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  printf("SDL2 compiler version: %d.%d.%d ...\n", compiled.major,
         compiled.minor, compiled.patch);
  printf("SDL2 linked version: %d.%d.%d.\n", linked.major, linked.minor,
         linked.patch);

  /* Initiate display */
  if (success == TRUE) {
    globalwindow = SDL_CreateWindow("hikingGPS!!", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, 0);
    if (globalwindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = FALSE;
    }
  }

  /*
   * Create GLOBAL renderer, use "software renderer" for now
   * see SDL_render.c in SDL2sources
   */
  if (success == TRUE) {
    /* print available renderer drivers */
    r = SDL_GetNumRenderDrivers();
    printf("NumRenderDrivers = %d\n", r);
    i = 0;
    while (i < r) {
      if (SDL_GetRenderDriverInfo(i, &info) == 0) {
        printf("  render driver %d = %s ", i, info.name);
        printf("    flags(hex) = %x\n", info.flags);
        printf("    num texture formats = %d\n", info.num_texture_formats);
        printf("    texture max width, height = %d, %d\n",
               info.max_texture_width, info.max_texture_height);
      }
      i++;
    }

    /* initialize renderer */
    globalrenderer = SDL_CreateRenderer(globalwindow, -1, 0);
    if (globalrenderer == NULL) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      success = FALSE;
    } else {
      /* print selected renderer */
      SDL_GetRendererInfo(globalrenderer, &info);
      printf(" Selected Renderer = %s\n", info.name);
    }
    /* init render draw colour default = white */
    if (SDL_SetRenderDrawColor(globalrenderer, 0xFF, 0xFF, 0xFF, 0xFF) < 0 )
      printf("SDL draw color = white failed %s\n", SDL_GetError());
  }

  /* Initialize PNG, TIF, JPG loading */
  if (success == TRUE) {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
      printf("SDL_image could not initialize! SDL_image Error: %s\n",
             IMG_GetError());
      success = FALSE;
    }
  }



  /* Initialize SDL_ttf */
  if (success && TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    success = FALSE;
  }

  /* test screen on display 
  SDL_RenderClear(globalrenderer);
  SDL_RenderPresent(globalrenderer);

  printf("SDL2init complete\n");
  printf( "white screen should appear on display for 4 sec\n\n\n");
  SDL_Delay(4000);
 */

  return (success);
}

/**
 * closeSDL2() - close SDL2, set global variables to NULL
 * Return: nothing
 */
void closeSDL2() {

  /* Destroy window */
  SDL_DestroyRenderer(globalrenderer);
  SDL_DestroyWindow(globalwindow);
  globalwindow = NULL;
  globalrenderer = NULL;

  IMG_Quit();
  SDL_Quit();
}



