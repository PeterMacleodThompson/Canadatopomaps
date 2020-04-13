/**
 * DOC: -- savegraymap.c -- saves array of grayscale pixel values to .pgm file
 * Peter Thompson 2020
 *
 *
 * outputs pre.pgm (before conversion), and post.pgm (after conversion)
 * for local viewing via gimp
 *
 * DEGUB HELPER
 * THIS CAN BE DELETED WITHOUT IMPACT.   REMOVE LINE 71,75,99 IN collarcalc.c
 */

#include <stdint.h> /* for uint8 */
#include <stdio.h>

/**
 * saveas() - convert dark pixels in collars to white
 * @array:  1 dimensional array of gray pixels: 0=black, 255=white
 * @width:  width of map array
 * @height: height of map array
 * @filename: current mapset
 * Return: nothing
 */

int saveas(uint8_t *array, int width, int height, char *filename) {
  FILE *fp;
  int i, x, y, temp;

  fp = fopen(filename, "w");
  if (fp == NULL)
    return (-1);
  fprintf(fp, "P2\n"); /* magic number for .pgm files */
  fprintf(fp, "%d %d\n", width, height);
  fprintf(fp, "255\n"); /* max y value */
  i = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      temp = array[y * width + x];
      fprintf(fp, "%d \n", temp);
      i++;
    }
  }
  fclose(fp);
  return (i);
}
