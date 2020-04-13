/**
 * DOC: -- noblack.c -- converts gray pixels in map-array collar to black
 * Peter Thompson 2020
 *
 * converts map-array pixels from gray to white based on
 * mapset.noblack.   mapset.noblack defaults to 25 which means
 * all pixels in collars defined in mapset.collarN, S, E, W
 * which are <= 25 (black or dark gray) are converted to white.
 *
 * outputs pre.pgm (before conversion), and post.pgm (after conversion)
 * for local viewing via gimp
 */

#include "maps.h"
#include <stdint.h> /* for uint8 */
#include <stdio.h>

/**
 * noblack() - convert dark pixels in collars to white
 * @array:  1 dimensional array of gray pixels: 0=black, 255=white
 * @width:  width of map array
 * @height: height of map array
 * @mapsetnow: current mapset
 * Return: count of collar pixels whitened OR -1 if error
 */
int noblack(uint8_t *array, int width, int height, mapset *mapsetnow) {
  int x, y;
  int cnt;

  cnt = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      /* noblack conversion of collar pixels */
      if ((y < mapsetnow->collarN || y > mapsetnow->collarS ||
           x < mapsetnow->collarW || x > mapsetnow->collarE) &&
          (array[y * width + x] < mapsetnow->noblack)) {
        array[y * width + x] = 255;
        cnt++;
      }
    }
  }
  return (cnt);
}
