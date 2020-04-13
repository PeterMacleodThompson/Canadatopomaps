/**
 * DOC: -- find250kmap.c -- given longitude, latitude, find the associated 250k
 * map(s) Peter Thompson 2020
 *
 * For Canada 250k maps, longitude latitude can be calculated from the mapid
 * latitude = 40 + 4*mapid[2] + charconvert(mapid[3])
 * longitude = 48.0 + 8*mapid[1] + charconvert(mapid[3]);
 * eg - 031e = 40 + 4*'1' + 2 where charconvert('e') = 2
 *           = 46.0 degrees   is the North Latitude.
 *  South latitude is 1.0 degree less than North Latitude.
 *
 *  The REVERSE (VERSO) calculation for latitude is
 * mapid[2] = (int) (latitude - 40) / 4 designates numeric value 0...9
 * Modulus (remainder) of (latitdue - 40) / 4 is the character...
 *  0 -> a,b,c,d
 *  1 -> e,f,g,h
 *  2 -> i,j,k,l
 *  3 -> m,n,o,p
 *
 * eg Percy Lake long,lat =  78.36972222 45.21916667
 * verso = (45.21916667 - 40) / 4 = 1  ==> mapid = 0x1?
 * modulus (45.21916667 - 40) / 4 = 1  ==> mapid = 0x1e (or 2nd row)
 *
 *  The REVERSE (VERSO) calculation for longitude is
 * mapid[2] = (int) (longitude - 48) / 8 designates numeric value 0...9
 * Modulus (remainder) of (latitdue - 40) / 4 is the character...
 *  0 -> a,b,c,d
 *  1 -> e,f,g,h
 *  2 -> i,j,k,l
 *  3 -> m,n,o,p
 *
 * eg Percy Lake long,lat =  78.36972222 45.21916667
 * verso = (78.36972222 - 48) / 8 = 3  ==> mapid = 03x?
 * modulus (78.36972222 - 48) / 8 = 6/2 = 3  ==> mapid = 03xe (or 4th column)
 */

/**
 * convert integer of longitude and integer of latitude
 * to 250k map symbol a,b,c,..p

 * NOTE the array columns, rows seem inverted
 * when compared to maps because arrays increase
 *  left to right but longitude in Canada increases right to left
 *  and rows increase top to bottom, but latitude increases
 *  bottom to top.
 */
#include <stdio.h>
#include <string.h>

char *find250kmap(double longitude, double latitude) {
  static char mapid[10];
  /* rest of Canada */
  static char lookup1[4][4] = {
      {'a', 'b', 'c', 'd'},
      {'h', 'g', 'f', 'e'},
      {'i', 'j', 'k', 'l'},
      {'p', 'o', 'n', 'm'},
  };
  /* far north */
  static char lookup2[4][4] = {
      /* FIXME LOOKS WRONG SHOULD BE [4][2] */
      {'a', 'b'},
      {'d', 'c'},
      {'e', 'f'},
      {'h', 'g'},
  };
  int i, j, k;

  /* north pole */
  if (latitude > 80.0) {
    if (longitude > 88)
      strcpy(mapid, "560a");
    else if (longitude > 72.0)
      strcpy(mapid, "340a");
    else
      strcpy(mapid, "120a");

    i = (int)(latitude - 40.0) % 4;
    j = ((int)(longitude - 48.0) % 8) / 4;
    mapid[3] = lookup2[i][j];
  }

  /* rest of Canada */
  else {
    k = (int)(longitude - 48.0) / 8;
    if (k > 9) {
      mapid[0] = '1';
      mapid[1] = (k % 10) + '0'; /* integer to char */
    } else {
      mapid[0] = '0';
      mapid[1] = k + '0';
    }
    mapid[2] = ((int)(latitude - 40.0) / 4) + '0'; /* integer to char */

    i = (int)(latitude - 40.0) % 4; /* remainder */

    if (latitude < 68.0) {
      j = ((int)(longitude - 48.0) % 8) / 2;
      mapid[3] = lookup1[i][j]; /* rest of Canada */
    } else {
      j = ((int)(longitude - 48.0) % 8) / 4;
      mapid[3] = lookup2[i][j]; /* far north */
    }
    mapid[4] = '\0'; /* end of string */
  }
  printf("mapid = %s from %lf, %lf\n", mapid, latitude, longitude);
  return (mapid);
}
