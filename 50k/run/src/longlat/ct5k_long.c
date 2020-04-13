/**
 * DOC: -- ct5k_long.c -- calculate East, West longitude of 50k map
 * Peter Thompson 2020
 *
 * For Canada 50k maps, longitude can be calculated from the 6 char mapid
 * The 1st 4 char are converted by long.c in 250maps giving degrees
 * The next 2 char digits  equated to 1 of 4 columns and
 *  converted to 0, .5, 1.0, 1.5 to add to East longitude from 250k map.
 * returns longE or longW
 */

/* function prototypes */
double longE(char *);

/**
 * ct5k_longE() - find longitude of east edge of map
 * @mapid: 6 character id of 50k map
 * return (double): longitude in decimal degrees 99.9999
 */
double ct5k_longE(char mapid[]) {
  double llong;
  int x, digit1, digit10;
  if (mapid[0] == '\0')
    return (0.0);
  llong = longE(mapid);
  digit1 = mapid[5] - '0'; /* convert char to digit */
  digit10 = mapid[4] - '0';
  x = (digit10 * 10) + digit1; /* integers 1,2,...15,16 */

  /* North Pole exception handling */
  if (mapid[0] > '0') {
    if (x == 1 || x == 8 || x == 9 || x == 16) /* column east */
      return (llong);
    if (x == 2 || x == 7 || x == 10 || x == 15)
      return (llong + 2.0);
    if (x == 3 || x == 6 || x == 11 || x == 14)
      return (llong + 4.0);
    if (x == 4 || x == 5 || x == 12 || x == 13) /* column west */
      return (llong + 6.0);
    return (0.0); /* default */
  }

  /*  Far North exception handling */
  else if (mapid[2] > '6') {
    if (x == 1 || x == 8 || x == 9 || x == 16) /* column east */
      return (llong);
    if (x == 2 || x == 7 || x == 10 || x == 15)
      return (llong + 1.0);
    if (x == 3 || x == 6 || x == 11 || x == 14)
      return (llong + 2.0);
    if (x == 4 || x == 5 || x == 12 || x == 13) /* column west */
      return (llong + 3.0);
    return (0.0); /* default */
  }

  /* Normal Canada handling */
  else {
    if (x == 1 || x == 8 || x == 9 || x == 16) /* column east */
      return (llong);
    if (x == 2 || x == 7 || x == 10 || x == 15)
      return (llong + 0.5);
    if (x == 3 || x == 6 || x == 11 || x == 14)
      return (llong + 1.0);
    if (x == 4 || x == 5 || x == 12 || x == 13) /* column west */
      return (llong + 1.5);
    return (0.0); /* default */
  }
}

/**
 * ct5k_longW() - find longitude of west edge of map
 * @mapid: 6 character id of 50k map
 * return (double): longitude in decimal degrees 99.9999
 */
double ct5k_longW(char mapid[]) { return (ct5k_longE(mapid) + 0.5); }
