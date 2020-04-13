/**
 * DOC: -- collarcalc.c -- calculate collar for mapnow, update mapindexnow
 * Peter Thompson 2020
 *
 *  mostly print statements with calls to functions which do the work.
 *  Updates mapindex "now" with North, South, East, West  pixel locations
 *    for collars.
 */

#include "display.h"
#include "maps.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* function prototypes */
Uint8 *buildarray(char *);
int arraywidth();
int arrayheight();
int noblack(uint8_t *, int, int, mapset *);
int saveas(uint8_t *, int, int, char *);
int mapmean(uint8_t *, int, int, mapset *);
int collarmean(uint8_t *, int, int, mapset *);
int northline(uint8_t *, int, int, int, int, mapset *);
int southline(uint8_t *, int, int, int, int, mapset *);
int westline(uint8_t *, int, int, int, int, mapset *);
int eastline(uint8_t *, int, int, int, int, mapset *);
void lineavg(uint8_t *, int, int, mapset *);
mapset *mapsetnow();
mapindex *mapindexinfo();
char *getmappath();

int ct_collarcalc() {
  mapset *mymapset;
  mapindex *mymap;
  Uint8 *pixelmap;
  int err;
  int collaravg, mapavg;
  char string[500];

  mymapset = mapsetnow();
  mymap = mapindexinfo();
  if (mymapset == NULL || mymap == NULL || err < 0) {
    printf(" Error in opening mapset, map, or SDL2\n");
    return (-1);
  }
  strcpy(string, getmappath());
  strcat(string, mymapset->name);
  strcat(string, "/raw/");
  strcat(string, mymap->mapimagename);
  pixelmap = buildarray(string);
  if (pixelmap == NULL)
    return (-1);
  printf("size of %s = %d width, %d height\n", mymap->mapimagename,
         arraywidth(), arrayheight());
  printf(" pixel(0,0) = %d\n", pixelmap[0]);
  /*  saveas( pixelmap, arraywidth(), arrayheight(), "gray.pgm");  DEBUG HELPER
   */

  err = noblack(pixelmap, arraywidth(), arrayheight(), mymapset);
  printf("# of pixels converted black to white = %d\n", err);
  /*  saveas( pixelmap, arraywidth(), arrayheight(), "whiten.pgm");    DEBUG
   * HELPER */

  mapavg = mapmean(pixelmap, arraywidth(), arrayheight(), mymapset);
  printf("map mean = %d\n", mapavg);
  collaravg = collarmean(pixelmap, arraywidth(), arrayheight(), mymapset);
  printf("collar mean = %d\n", collaravg);

  /*  lineavg( pixelmap, arraywidth(), arrayheight(), mymapset);  DEBUG HELPER
   */

  mymap->collarNEy = mymap->collarNWy = northline(
      pixelmap, mapavg, collaravg, arraywidth(), arrayheight(), mymapset);
  printf("northline = %d\n\n", mymap->collarNEx);

  mymap->collarSEy = mymap->collarSWy = southline(
      pixelmap, mapavg, collaravg, arraywidth(), arrayheight(), mymapset);
  printf("southline = %d\n\n", mymap->collarSEy);

  mymap->collarNWx = mymap->collarSWx = westline(
      pixelmap, mapavg, collaravg, arraywidth(), arrayheight(), mymapset);
  printf("westline = %d\n\n", mymap->collarNWx);

  mymap->collarNEx = mymap->collarSEx = eastline(
      pixelmap, mapavg, collaravg, arraywidth(), arrayheight(), mymapset);
  printf("eastline = %d\n\n", mymap->collarNEx);
  /* remove gray.pgm */
  return (1);
}
