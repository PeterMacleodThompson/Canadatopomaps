/**
 * DOC: -- lat.c -- calculate North, South latitude of map
 * Peter Thompson 2020
 *
 * For Canada 250k maps, latitude can be calculated from the mapid
 * latitude = 40 + 4*mapid[2] + charconvert(mapid[3])
 * eg - 031e = 40 + 4*'1' + 2 where charconvert('e') = 2
 *           = 46.0 degrees   is the North Latitude.
 *  South latitude is 1.0 degree less than North Latitude.
 */

/**
 * charconvert() - convert 250k map symbol a,b,c,..p to integer of latitude
 * @mapid: 4 character id of 250k map
 * convert mapid char to number
 * return: integer latitude of degrees to be added
 */
static int charconvert(char mapid[]) {
  int x;

  x = 0;
  if (mapid[0] > '0' || mapid[2] > '6') {
    if (mapid[3] == 'a' || mapid[3] == 'b')
      x = 1;
    else if (mapid[3] == 'c' || mapid[3] == 'd')
      x = 2;
    else if (mapid[3] == 'e' || mapid[3] == 'f')
      x = 2;
    else if (mapid[3] == 'g' || mapid[3] == 'h')
      x = 2;
  } else {
    if (mapid[3] == 'a' || mapid[3] == 'b' || mapid[3] == 'c' ||
        mapid[3] == 'd')
      x = 1;
    else if (mapid[3] == 'e' || mapid[3] == 'f' || mapid[3] == 'g' ||
             mapid[3] == 'h')
      x = 2;
    else if (mapid[3] == 'i' || mapid[3] == 'j' || mapid[3] == 'k' ||
             mapid[3] == 'l')
      x = 3;
    else if (mapid[3] == 'm' || mapid[3] == 'n' || mapid[3] == 'o' ||
             mapid[3] == 'p')
      x = 4;
  }
  return (x);
}

/**
 * latN() - find latitude of north edge of map
 * @mapid: 4 character id of 250k map
 * return (double): latitude in decimal degrees 99.9999
 */
double latN(char mapid[]) {
  double x, y;

  if (mapid[0] == '\0')
    return (0.0);
  x = (double)charconvert(mapid);
  y = 40.0 + 4.0 * (int)(mapid[2] - '0') + x;
  return (y);
}

/**
 * latS() - find latitude of south edge of map
 * @mapid: 4 character id of 250k map
 * return (double): latitude in decimal degrees 99.9999
 */
double latS(char mapid[]) {
  if (mapid[0] == '\0')
    return (0.0);
  else
    return (latN(mapid) - 1.0);
}
