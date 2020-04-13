/**
 * DOC: -- northline.c -- finds border between map and north collar
 * Peter Thompson 2020
 *
 * uses difference in greyscale between map average greyscale (normally dark
grey)
 * collar average greyscale (normally white) to locate pixel marking border
between
 * them
 *
 * TRY GIMP>FILTER>BLUR>PIXELIZE>5X5 PIXEL BLOCK
 *  USE IMAGE KERNEL >SHARPEN   http://setosa.io/ev/image-kernels/
 *     and set parameters as high as possible
 *

For this to work must
   1. convert the image to greyscale (done in buildarray)
     gimp> image>mode>greyscale
   2 convert all pixels < 100 (dark grey or black assuming 0-225 colour scale)
      to white.     this converts all lettering on border to white
     and leaves the map grey for better collar vs map grayscale averages.
     gimp>  colors> map > color exchange
             black to white,  thresholds at ,50


 * Look for corner line North
 * move north from map until single (1) midpoint between
 * collar average and map average is reached.
 * Repeat moving south from collar.
 * If they match, we have found the corner line
 * If not match, continue looking for 2 in a row
 * then 3 in a row until corner line is found
 * whereby southbound line = northbound line
 * This is a candidate corner.
 * If xcollarN is reached, Error.  Cannot find corner.

return -1 if error
return pixel line
 */

#include "maps.h"
#include <stdint.h> /* for uint8_t */
#include <stdio.h>

#define GONORTH 0
#define GOSOUTH 1

/**
 * northline() - find north edge of map
 * @array: pointer to grayscale version of map 0=black, 255=white
 * @mapavg: average grayscale value of map
 * @collaravg: average grayscale value of collar
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset

 * Return: y pixel of north edge of map
 *         -1 if no edge found
 */
int northline(uint8_t *array, int mapavg, int collaravg, int width, int height,
              mapset *mapsetnow) {
  int ynorthline; /* northline pixel */
  int ysouthline;
  int gnxstart, gnxend, gnystart, gnyend; /* go north (x,y) */
  int gsxstart, gsxend, gsystart, gsyend; /* go south (x,y)*/
  int gns;                                /* go north, go south flag */
  double pixelN, pixelE, pixelW;
  double threshold; /* extra pixels away from guess line */
  int x, y, i;
  double sum, midpoint, avg;

  if (mapavg >=
      collaravg) /* assume collar is white  with significant difference */
    return (-1);
  midpoint = (mapavg + collaravg) / 2.0;

  pixelN = mapsetnow->collarN / 100.0 * (double)height;
  pixelE = mapsetnow->collarE / 100.0 * (double)width;
  pixelW = mapsetnow->collarW / 100.0 * (double)width;

  /* set the southline-GONORTH (gn) parameters */
  threshold = 0.1 * (double)height;
  gnxstart = pixelE;
  gnxend = width - pixelW;
  gnystart = pixelN + threshold; /* 10% south of estimated line */
  gnyend = 0;
  ysouthline = gnystart;

  /* set the northline-GOSOUTH (gs) parameters */
  gsxstart = pixelE;
  gsxend = width - pixelW;
  gsystart = 0;
  gsyend = pixelN + threshold; /* 10% south of estimated line */
  ynorthline = gsystart;

  gns = GONORTH; /* can start NORTH or SOUTH */
  sum = 0.0;
  i = 0;

  while (ysouthline > ynorthline) {
    if (gns == GONORTH) {
      i = 0;
      sum = 0.0;
      for (y = gnystart; y >= gnyend; y--) {
        for (x = gnxstart; x < gnxend; x++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this line is THE collar border line */
        avg = sum / i;
        if (avg > midpoint || y <= ynorthline) {
          printf("GONORTH SET ysouthline (northly progress) = %d\n", y);
          ysouthline = y;
          gnystart = y - 1;
          gns = GOSOUTH;
          break;
        }
        /* reset to see if next line is THE collar border line */
        sum = 0.0;
        i = 0;
      }
    } else if (gns == GOSOUTH) {
      sum = 0.0;
      i = 0;
      for (y = gsystart; y <= gsyend; y++) {
        for (x = gsxstart; x < gsxend; x++) {
          sum += array[y * width + x];
          i++;
        }
        /* check if this line is THE collar border line */
        avg = sum / i;
        if (avg < midpoint || y >= ysouthline) {
          printf("GOSOUTH SET ynorthline (southly progress) = %d\n", y);
          ynorthline = y;
          gsystart = y + 1;
          gns = GONORTH;
          break;
        }
        /* reset to see if next line is THE collar border line */
        sum = 0.0;
        i = 0;
      }
    }
  }
  printf("FINISHED northline.c\n");
  printf("FOUND ynorthline = %d, ysouthline - %d\n", ynorthline, ysouthline);
  return (ysouthline);
}
