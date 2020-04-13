/**
 * DOC: -- find50kmap.c -- given longitude, latitude, find the associated 50k
 * map(s) Peter Thompson 2020
 *
 * use find250kmap.c to find 1st 4 characters of mapid.
 * use find50kmap.c (this program) to find last 2 digits of mapid
 * specifically one of 16 maps....  1,2,3....14,15,16
 *
 * In Canada topographic, the 16 50k maps in a 250 map is a 4x4 matrix
 * representing 2 degrees wide (East West), and 1 degree high (North South).
 * making each map 0.5 degrees wide and 0.25 degrees high.
 *
 * We solve the 4x4 matrix REVERSED.   The maps (and degrees) start in SE
 * corner. Our matrix starts in NW corner.
 */

#include <math.h>
#include <stdio.h>

char *find50kmap(double longitude, double latitude) {
  static char suffix[20];
  int row, col;
  double latf, longf, longi, dbl;
  double *ip;
  const static int lookup[4][4] = {
      {1, 2, 3, 4}, {8, 7, 6, 5}, {9, 10, 11, 12}, {16, 15, 14, 13}};

  /* find row */
  ip = &dbl;
  latf = modf(latitude, ip); /* 1 degree difference, use fractional*/
  if (latf < 0.25)
    row = 0;
  else if (latf < 0.5)
    row = 1;
  else if (latf < 0.75)
    row = 2;
  else
    row = 3;

  /* find column */
  longf = modf(longitude, ip); /* 2 degrees difference, use fractional + */
  longi = ((int)dbl) % 2;      /* remainder of integer division by 2 */
  longf += (double)longi;
  if (longf < 0.5)
    col = 0;
  else if (longf < 1.0)
    col = 1;
  else if (longf < 1.5)
    col = 2;
  else
    col = 3;
  sprintf(suffix, "%02d", lookup[row][col]); /* convert integer to ascii */
  return (suffix);
}
