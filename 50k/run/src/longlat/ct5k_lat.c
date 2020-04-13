/**
 * DOC: -- ct5k_lat.c -- calculate North, South latitude of 50k map
 * Peter Thompson 2020
 *
 * For Canada 50k maps, latitude can be calculated from the 6 char mapid
 * The 1st 4 char are converted by lat.c in 250maps giving degrees
 * The next 2 char digits are divided by 4 to give 0, .25, .5, .75 degrees
 * returns latN or latS
 */

/* function prototypes */
double latS(char *);

/**
 * ct5k_latS() - find latitude of south edge of map
 * @mapid: 6 character id of 50k map
 * return (double): latitude in decimal degrees 99.9999
 */
double ct5k_latS(char mapid[]) {
  double lat;
  int y, digit1, digit10;
  if (mapid[0] == '\0')
    return (0.0);
  lat = latS(mapid);
  digit1 = mapid[5] - '0'; /* convert char to digit */
  digit10 = mapid[4] - '0';
  y = (digit10 * 10) + digit1;           /* integers 1,2,...15,16 */
  lat = lat + (int)((y - 1) / 4) * 0.25; /* convert 1,2,.. to decimal degrees */
  return (lat);
}

/**
 * latN() - find latitude of north edge of map
 * @mapid: 6 character id of 50k map
 * return (double): latitude in decimal degrees 99.9999
 */
double ct5k_latN(char mapid[]) {
  if (mapid[0] == '\0')
    return (0.0);
  else
    return (ct5k_latS(mapid) + .25);
}
