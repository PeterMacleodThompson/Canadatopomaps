/**
 * DOC: -- eastline.c -- finds border between map and east collar
 * Peter Thompson 2020
 *
 * Algorithm:
 *
 * see southline.c for program documentation
 * but this is columns, not rows.
 */

#include "maps.h"
#include <stdint.h> /* for uint8_t */
#include <stdio.h>

#define GOEAST 0
#define GOWEST 1

/**
 * eastline() - find east edge of map
 * @array: pointer to grayscale version of map 0=black, 255=white
 * @mapavg: average grayscale value of map
 * @collaravg: average grayscale value of collar
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset
 *
 * Return: y pixel of east edge of map
 *         -1 if no edge found
 */
int eastline(uint8_t *array, int mapavg, int collaravg, int width, int height,
             mapset *mapsetnow) {
  int xwestcolumn, xeastcolumn;
  int gwxstart, gwxend, gwystart, gwyend; /* go west (x,y) */
  int gexstart, gexend, geystart, geyend; /* go east (x,y)*/
  int gew;                                /* go north, go south flag */
  double pixelN, pixelS, pixelE;
  double threshold; /* extra pixels away from guess line */
  int x, y, i;
  int sum, midpoint, avg;

  if (mapavg >=
      collaravg) /* assume collar is white  with significant difference */
    return (-1);
  midpoint = (mapavg + collaravg) / 2.0;

  pixelN = mapsetnow->collarN / 100.0 * (double)height;
  pixelS = mapsetnow->collarS / 100.0 * (double)height;
  pixelE = mapsetnow->collarE / 100.0 * (double)width;

  /* set the westcolumn-GOEAST (ge) parameters */
  threshold = 0.2 * (double)width; /* threshold = 20% */
  geystart = pixelN;
  geyend = height - pixelS;
  gexstart = width - (pixelE + threshold);
  gexend = width;
  xwestcolumn = gexstart;

  /* set the eastcolumn-GOWEST (gw) parameters */
  gwystart = pixelN;
  gwyend = height - pixelS;
  gwxstart = width;
  gwxend = width - (pixelE + threshold);
  xeastcolumn = gwxstart;

  gew = GOWEST; /* can start EAST or WEST */
  i = sum = 0;
  while (xeastcolumn > xwestcolumn) {
    if (gew == GOWEST) {
      i = sum = 0;
      for (x = gwxstart; x >= gwxend; x--) {
        for (y = gwystart; y < gwyend; y++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this column is THE collar border column */
        avg = sum / i;
        if (avg < midpoint || x <= xwestcolumn) {
          printf("GOWEST SET xeastcolumn (westerly progress) = %d\n", x);
          xeastcolumn = x;
          gwxstart = x - 1;
          gew = GOEAST;
          break;
        }
        i = sum = 0; /* reset for next line */
      }
    } else if (gew == GOEAST) {
      i = sum = 0;
      for (x = gexstart; x <= gexend; x++) {
        for (y = geystart; y < geyend; y++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this line is THE collar border line */
        avg = sum / i;
        if (avg > midpoint || x >= xeastcolumn) {
          printf("GOEAST SET xwestcolumn (easterly progress) = %d\n", x);
          xwestcolumn = x;
          gexstart = x + 1;
          gew = GOWEST;
          break;
        }
        i = sum = 0; /* reset for next line */
      }
    }
  }
  printf("FINISHED eastline.c\n");
  printf("FOUND xeastcolumn = %d, xwestcolumn = %d\n", xeastcolumn,
         xwestcolumn);
  return (xeastcolumn);
}
