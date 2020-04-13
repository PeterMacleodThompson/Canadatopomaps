/**
 * DOC: -- buildarray.c -- converts SDL image to array of grey pixels
 * Peter Thompson 2020
 *
 * reads a .jpg, .png image and creates a greyscale equivalent array.
 * in creating greyscale, any pixel <25 (dark grey) is converted to 255 (white)
 * to help remove black borders around map and remove labels, letters in collar
 * so they are not part of collar average grayscale.
 *    Follows
https://dzone.com/articles/converting-an-image-to-grayscale-using-sdl2
http://gigi.nullneuron.net/gigilabs/converting-an-image-to-grayscale-using-sdl2/
https://www.cs.swarthmore.edu/~newhall/unixhelp/C_arrays.html
 *
 *    buildarray()
 *    arraywidth()
 *    arrayheight()
 *    ct_collarmark()
 *    freearray()
 *
 */

#include "maps.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/* function prototypes */
char *getmappath(void);
mapindex *mapindexinfo();
mapset *mapsetnow(void);

static int width; /* pixel count for width, height of raw image */
static int height;
static SDL_Surface *image;
static Uint8 *array;

/**
 * buildarray() -converts SDL image to array of grey pixels
 * @filename or image, read into SDL, and converted to array
 * Return: Uint8 array of greyscale pixels
 */
Uint8 *buildarray(char *filename) {

  SDL_PixelFormat *fmt;
  Uint32 surfaceformat;
  Uint32 *pixels; /* pointer to map*/
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  mapset *mapsetnow(void);
  Uint8 b;
  Uint8 grey;
  int x, y;
  int total;

  /* load map into sdl surface */
  image = IMG_Load(filename);
  if (image == NULL) {
    printf(" file not exist %s\n", filename);
    return (NULL);
  }
  fmt = image->format;
  surfaceformat = fmt->format;
  printf("Pixel format of %s is %s\n", filename,
         SDL_GetPixelFormatName(surfaceformat));
  image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_ARGB8888, 0);
  printf("...converted to ARGB8888\n");
  width = image->w;
  height = image->h;

  /*  initialize array with map */
  array = malloc(sizeof(Uint8) * image->w * image->h);
  if (array == NULL) {
    printf("insufficient memory for file %s width=%d, height=%d\n", filename,
           image->w, image->h);
    return (NULL);
  }
  /* convert map to greyscale - copy to array */
  total = 0;
  pixels = (Uint32 *)image->pixels;
  for (y = 0; y < image->h; y++) {
    for (x = 0; x < image->w; x++) {
      total++;
      pixel = pixels[y * image->w + x];
      /* convert to greyscale */
      r = pixel >> 16 & 0xFF;
      g = pixel >> 8 & 0xFF;
      b = pixel & 0xFF;
      grey = (r + g + b) / 3;
      array[y * image->w + x] = grey;
    }
  }
  printf("build array size w,h, total = %d, %d, %d\n", width, height, total);
  return (array);
}

int arraywidth() { return (width); }

int arrayheight() { return (height); }

/**
 * collarmark()   mark collar on current map, save in /collarNOW.bmp
 *  6 pixel line (colour rgb = 89. 247, 10) centered on collar pixel
 */
void ct_collarmark() {
  mapindex *mymap;
  Uint32 *pixels; /* pointer to map*/
  int x, y;
  char savemap[400];
  mapset *mapsetp;

  mymap = mapindexinfo();

  pixels = (Uint32 *)image->pixels;
  /* north line */
  for (y = mymap->collarNWy - 3; y < mymap->collarNWy + 3; y++)
    for (x = mymap->collarNWx - 3; x < mymap->collarNEx + 3; x++)
      /* convert pixel to bright green: rgb = 89,247,10 = 0x59f70a */
      pixels[y * image->w + x] = 0xff59f70a;
  /* south line */
  for (y = mymap->collarSWy - 3; y < mymap->collarSWy + 3; y++)
    for (x = mymap->collarSWx - 3; x < mymap->collarSEx + 3; x++)
      /* convert pixel to bright green: rgb = 89,247,10 = 0x59f70a */
      pixels[y * image->w + x] = 0xff59f70a;
  /* west line */
  for (y = mymap->collarNWy - 3; y < mymap->collarSWy + 3; y++)
    for (x = mymap->collarNWx - 3; x < mymap->collarNWx + 3; x++)
      /* convert pixel to bright green: rgb = 89,247,10 = 0x59f70a */
      pixels[y * image->w + x] = 0xff59f70a;
  /* east line */
  for (y = mymap->collarNEy - 3; y < mymap->collarSEy + 3; y++)
    for (x = mymap->collarNEx - 3; x < mymap->collarNEx + 3; x++)
      /* convert pixel to bright green: rgb = 89,247,10 = 0x59f70a */
      pixels[y * image->w + x] = 0xff59f70a;
  /*save the map */
  strcpy(savemap, getmappath());
  mapsetp = mapsetnow();
  strcat(savemap, mapsetp->name);
  strcat(savemap, "/");
  strcat(savemap, "collarnow.bmp");
  SDL_SaveBMP(image, savemap);
}

void freearray() {
  SDL_FreeSurface(image);
  free(array);
}
