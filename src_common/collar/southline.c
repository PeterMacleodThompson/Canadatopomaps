/**
 * DOC: -- northline.c -- finds border between map and north collar
 * Peter Thompson 2020
 *
 * Algorithm:
 * based on map 031e - height=6571, width=8733
 * compute a revised collar
 *   =  estimated collar from mapset(12%) + 20% threshold ==> eg 2102
 *   subtracted from height = 6571-2102=4469
 * calculate midpoint between map average grayscale, collar average grayscale
 * (215 + 240) = 227
 * GONORTH
 *   start at bottom of image in collar (eg 6571)
 *   compute average grayscale for line of pixels.
 *   GONORTH (y--) until outside collar = inside map - ie average < midpoint
 *   if outside collar, save y, then GOSOUTH.  Otherwise keep going GONORTH
 * GOSOUTH
 *    start inside map at revised collar eg 4469
 *    GOSOUTH (y++) until outside map. - ie average > midpoint
 *
 * see also  northline.c for program documentation
 */

#include "maps.h"
#include <stdint.h> /* for uint8_t */
#include <stdio.h>

#define GONORTH 0
#define GOSOUTH 1

/**
 * southline() - find south edge of map
 * @array: pointer to grayscale version of map 0=black, 255=white
 * @mapavg: average grayscale value of map
 * @collaravg: average grayscale value of collar
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset

 * Return: y pixel of south edge of map
 *         -1 if no edge found
 */
int southline(uint8_t *array, int mapavg, int collaravg, int width, int height,
              mapset *mapsetnow) {
  int ynorthline; /* northline pixel */
  int ysouthline;
  int gnxstart, gnxend, gnystart, gnyend; /* go north (x,y) */
  int gsxstart, gsxend, gsystart, gsyend; /* go south (x,y)*/
  int gns;                                /* go north, go south flag */
  double pixelS, pixelE, pixelW;
  double threshold; /* extra pixels away from guess line */
  int x, y, i;
  int sum, midpoint, avg;

  if (mapavg >=
      collaravg) /* assume collar is white  with significant difference */
    return (-1);
  midpoint = (mapavg + collaravg) / 2.0;

  pixelS = mapsetnow->collarS / 100.0 * (double)height;
  pixelE = mapsetnow->collarE / 100.0 * (double)width;
  pixelW = mapsetnow->collarW / 100.0 * (double)width;

  /* set the southline-GONORTH (gn) parameters */
  threshold = 0.2 * (double)height; /* threshold = 20% */
  gnxstart = pixelE;
  gnxend = width - pixelW;
  gnystart = height;
  gnyend = height - (pixelS + threshold); /* 10% north of estimated line */
  ysouthline = gnystart;

  /* set the northline-GOSOUTH (gs) parameters */
  gsxstart = pixelE;
  gsxend = width - pixelW;
  gsystart = height - (pixelS + threshold);
  gsyend = height; /* 10% south of estimated line */
  ynorthline = gsystart;

  gns = GONORTH; /* can start NORTH or SOUTH */
  i = sum = 0;

  while (ysouthline > ynorthline) {
    if (gns == GONORTH) {
      i = sum = 0;
      for (y = gnystart; y >= gnyend; y--) {
        for (x = gnxstart; x < gnxend; x++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this line is THE collar border line */
        avg = sum / i;
        if (avg < midpoint || y <= ynorthline) {
          printf("GONORTH SET ysouthline (northly progress) = %d\n", y);
          ysouthline = y;
          gnystart = y - 1;
          gns = GOSOUTH;
          break;
        }
        i = sum = 0; /* reset for next line */
      }
    } else if (gns == GOSOUTH) {
      i = sum = 0;
      for (y = gsystart; y <= gsyend; y++) {
        for (x = gsxstart; x < gsxend; x++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this line is THE collar border line */
        avg = sum / i;
        if (avg > midpoint || y >= ysouthline) {
          printf("GOSOUTH SET ynorthline (southly progress) = %d\n", y);
          ynorthline = y;
          gsystart = y + 1;
          gns = GONORTH;
          break;
        }
        i = sum = 0; /* reset for next line */
      }
    }
  }
  printf("FINISHED southline.c\n");
  printf("FOUND ynorthline = %d, ysouthline - %d\n", ynorthline, ysouthline);
  return (ynorthline);
}
