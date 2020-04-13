/**
 * DOC: -- arraystats.c -- computes mean, variance of array regions
 * Peter Thompson 2020
 *
 * computes mean, variance of map (central), and collar  (outer edge)
 * regions of an array of greyscale pixels.
 *
 */

#include "maps.h"
#include <stdint.h> /* for uint_8 */
#include <stdio.h>

/**
 * mapmean() - calculate average grayscale of entire map
 * @array: pointer to grayscale version of downloaded raw
 *    map image 0=black, 255=white
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset
 * Return: average grayscale value of map
 */
int mapmean(uint8_t *array, int width, int height, mapset *mapsetnow) {
  int xstart, xend, ystart, yend;
  double pixelN, pixelS, pixelE, pixelW;
  int i;
  double sum, average;

  pixelN = mapsetnow->collarN / 100.0 * (double)height;
  pixelS = mapsetnow->collarS / 100.0 * (double)height;
  pixelE = mapsetnow->collarE / 100.0 * (double)width;
  pixelW = mapsetnow->collarW / 100.0 * (double)width;
  xstart = (int)pixelE;
  xend = width - (int)pixelW;
  ystart = (int)pixelN;
  yend = height - (int)pixelS;
  printf("map xstart %d xend %d ystart %d yend %d\n", xstart, xend, ystart,
         yend);

  i = 0;
  sum = 0.0;
  for (int y = ystart; y < yend; y++) {
    for (int x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
  }
  average = sum / i;
  printf("map average = %lf, map pixelcount = %d\n", average, i);
  return (average);
}

/**
 * collarmean() - calculate average grayscale of collar
 * @array: pointer to grayscale version of downloaded raw
 *    map image 0=black, 255=white
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset
 * Return: average grayscale value of collar
 */
int collarmean(uint8_t *array, int width, int height, mapset *mapsetnow) {
  int xstart, xend, ystart, yend;
  double pixelN, pixelS, pixelE, pixelW;
  int i;
  double sum, average;

  pixelN = mapsetnow->collarN / 100.0 * (double)height;
  pixelS = mapsetnow->collarS / 100.0 * (double)height;
  pixelE = mapsetnow->collarE / 100.0 * (double)width;
  pixelW = mapsetnow->collarW / 100.0 * (double)width;
  i = 0;
  sum = 0.0;

  /* North Collar */
  xstart = ystart = 0;
  xend = width;
  yend = pixelN;
  for (int y = ystart; y < yend; y++) {
    for (int x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
  }

  /* South Collar */
  xstart = 0;
  xend = width;
  ystart = height - pixelS;
  yend = height;
  for (int y = ystart; y < yend; y++) {
    for (int x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
  }

  /* East Collar */
  xstart = 0;
  xend = pixelE;
  ystart = pixelN;
  yend = height - pixelS;
  for (int y = ystart; y < yend; y++) {
    for (int x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
  }

  /* West Collar */
  xstart = width - pixelW;
  xend = width;
  ystart = pixelN;
  yend = height - pixelS;
  for (int y = ystart; y < yend; y++) {
    for (int x = xstart; x < xend; x++) {
      sum += array[y * width + x];
      i++;
    }
  }

  /* calculate collar average */
  average = sum / i;
  printf("collar average = %lf, collar pixelcount = %d\n", average, i);
  return (average);
}
