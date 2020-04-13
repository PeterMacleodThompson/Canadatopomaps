/**
 * DOC: -- lineavg.c -- writes line & column averages of array
 * Peter Thompson 2020
 *
 * debug helper - computes pixel line averages same as northline.c, southline.c
 * etc and writes them to a files: line.txt and column.txt. THIS CAN BE DELETED
 * WITHOUT IMPACT.   REMOVE LINE 82 IN collarcalc.c
 */

#include "maps.h"
#include <stdint.h> /* for uint_8 */
#include <stdio.h>

/**
 * lineavg() - calculate average grayscale of entire map
 * @array: pointer to grayscale version of downloaded raw map image 0=black,
 * 255=white
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset
 * Return: nothing
 */

void lineavg(uint8_t *array, int width, int height, mapset *mapsetnow) {
  FILE *fp;
  int xstart, xend, ystart, yend;
  double pixelN, pixelS, pixelE, pixelW;
  int x, y;
  int i, sum, avg;

  /* line averages */
  fp = fopen("line.txt", "w");
  if (fp == NULL)
    return;

  pixelE = mapsetnow->collarE / 100.0 * (double)width;
  pixelW = mapsetnow->collarW / 100.0 * (double)width;
  xstart = (int)pixelE;
  xend = width - (int)pixelW;

  i = sum = 0;
  for (y = 0; y < height; y++) {
    for (x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
    avg = sum / i;
    fprintf(fp, "%d %d \n", y, avg);
    i = sum = 0;
  }
  fclose(fp);

  /* column averages */
  fp = fopen("column.txt", "w");
  if (fp == NULL)
    return;

  pixelN = mapsetnow->collarN / 100.0 * (double)height;
  pixelS = mapsetnow->collarS / 100.0 * (double)height;
  ystart = (int)pixelN;
  yend = height - (int)pixelS;

  i = sum = 0;
  for (x = 0; x < width; x++) {
    for (y = ystart; y < yend; y++) {
      sum += array[y * width + x];
      i++;
    }
    avg = sum / i;
    fprintf(fp, "%d %d \n", x, avg);
  }
  fclose(fp);
  return;
}
