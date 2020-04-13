/**
 * DOC: -- find1mmap.c -- given longitude, latitude, find the associated 1m
 * map(s) Peter Thompson 2020
 *
 * Map South Latitude calc
 * For Canada 1m maps, latitude can be calculated from 2nd char in mapid
 *   2nd char       = k, l, m, n, .... s, t, u
 *   which has lat  = 40, 44, 48, 52, ... 72, 76, 80
 *   ==> mapid[1] = 'k' + (lat-40)/4
 *  North latitude of map is 4.0 degree more than South Latitude.
 *
 * Map East Longitude calc
 * For Canada 1m maps, longitude is represented in the last 2 digits of mapid
 * where mapid digits   = 08, 09, 10, 11, .... 18, 19, 20, 21
 * represent longitude  = 132, 126, 120, 114, .... 72, 66, 60, 54
 * ==> mapid[2][3] = 08 + (132-long)/6
 * West longitude of 1m map is 6 degrees more than East longitude
 *    EXCEPTION far north 1m maps > 60 degrees (np, nq, nr, ns, nt, nu maps)
 *
 * eg Percy Lake long,lat =  78.36972222 45.21916667
 * mapid[0] = 'n' always
 * mapid[1] = 'k' + (45.21916667 - 40) / 4 = 'l'
 * mapid[3][4] =
 *   ==> mapid = nl17
 *
 */
#include <stdio.h>
#include <string.h>

char *find1mmap(double longitude, double latitude) {
  static char mapid[10];
  int calc;

  /* latitude calc */
  mapid[0] = 'n';
  mapid[1] = 'k' + ((int)(latitude - 40.0) / 4);

  /* longitude calc */
  if (mapid[1] >= 'p') {
    /* far north longitude calc */
    /* lookup in mapindex */
  } else {
    /* rest of Canada calc */
    calc = 8 + (int)(138 - longitude) / 6;
    mapid[2] = calc / 10 + '0';
    mapid[3] = calc % 10 + '0';
  }

  mapid[4] = '\0'; /* end of string */
  printf("mapid = %s from %lf, %lf\n", mapid, latitude, longitude);
  return (mapid);
}
