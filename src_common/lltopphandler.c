/**
 * DOC: -- lltopphandler.c  -- converts latitude, longitude to pixel points
 * Peter Thompson   -- 2020 March
 *
 * converts between longitude, latitude versus pixel points on an image.
 *
 * assumptions
 *  - the map is a rectangle (rarely true).  Accurate maps are
 *      a trapazoid with parallel arcs North and South latitude
 *      and lines angling in as they go north for longitude
 * - the map is to scale throughout
 * - this algorithm is more accurate at 1:50,000, less accurate at 1:1000,000
 *
 * Better Accuracy requires (TODO)
 *   - removal of collars OR accurate collar corners in mapindex
 *       change lltopphandler to pre-look for mapindex collars done manually
 *   - map should be rotated so it is square on the page
 *   - better algorithm to account for arc in latitude and different
 *       distances between top of map vs bottom of map  TODO
 */

#include "maps.h"
#include <stdio.h>

/**
 * ct_lltopp() lat/long to pixel position
 * @*latitude
 * @*longitude
 * @*pixelx
 * @*pixely
 * @info   copy of mapindex data of current map
 * returns 0 - pixelx, pixely are updated
 *
 * convert latitude longitude to pixel position (x,y) on current map
 */
int ct_lltopp(double *latitude, double *longitude, int *pixelx, int *pixely,
              mapindex info) {
  double fraction, distance;
  int maph, mapw;
  int collarNy, collarSy, collarEx, collarWx;
  if (info.pixelwidth == 0 || info.pixelheight == 0 || info.latN == 0.0 ||
      info.latS == 0.0) {
    printf("You must download map 1st, no action taken\n");
    return (0);
  }
  if (info.collarNWy == 0 && info.collarNWx == 0 && info.collarSEy == 0 &&
      info.collarSEx == 0) {
    /* no collars */
    maph = info.pixelheight;
    mapw = info.pixelwidth;
    collarNy = collarSy = collarEx = collarWx = 0;
  } else {
    /* collars */
    collarNy = (info.collarNWy + info.collarNEy) / 2;
    collarSy = ((info.pixelheight - info.collarSWy) +
                (info.pixelheight - info.collarSEy)) /
               2;
    collarEx = ((info.pixelwidth - info.collarNEx) +
                (info.pixelwidth - info.collarSEx)) /
               2;
    collarWx = (info.collarNWx + info.collarSWx) / 2;
    maph = info.pixelheight - (collarNy + collarSy);
    mapw = info.pixelwidth - (collarEx + collarWx);
  }
  fraction = ((double)info.latN - *latitude) / (double)(info.latN - info.latS);
  distance = fraction * (double)maph + 0.5;
  *pixely = distance + collarNy;

  fraction =
      ((double)info.longW - *longitude) / (double)(info.longW - info.longE);
  distance = fraction * mapw + 0.5;
  *pixelx = distance + collarWx;
  return (0);
}

/**
 * ct_pptoll() pixel position to lat/long
 * @*latitude
 * @*longitude
 * @*pixelx
 * @*pixely
 * @info   copy of mapindex data of current map
 * returns 0 - latitude, longitude are updated
 *
 * convert pixel position (x,y) on current map on latitude, longitude
 */
int ct_pptoll(double *latitude, double *longitude, int *pixelx, int *pixely,
              mapindex info) {
  double fraction, distance;
  int maph, mapw;
  int collarNy, collarSy, collarEx, collarWx;
  if (info.pixelwidth == 0 || info.pixelheight == 0 || info.latN == 0.0 ||
      info.latS == 0.0) {
    printf("You must download map 1st, no action taken\n");
    return (0);
  }
  if (info.collarNWy == 0 && info.collarNWx == 0 && info.collarSEy == 0 &&
      info.collarSEx == 0) {
    /* no collars */
    maph = info.pixelheight;
    mapw = info.pixelwidth;
    collarNy = collarSy = collarEx = collarWx = 0;
  } else {
    /* collars */
    collarNy = (info.collarNWy + info.collarNEy) / 2;
    collarSy = ((info.pixelheight - info.collarSWy) +
                (info.pixelheight - info.collarSEy)) /
               2;
    collarEx = ((info.pixelwidth - info.collarNEx) +
                (info.pixelwidth - info.collarSEx)) /
               2;
    collarWx = (info.collarNWx + info.collarSWx) / 2;
    maph = info.pixelheight - (collarNy + collarSy);
    mapw = info.pixelwidth - (collarEx + collarWx);
  }
  fraction = (double)(*pixely - collarNy) / (double)maph;
  distance = fraction * (double)(info.latN - info.latS);
  *latitude = (double)info.latN - distance;

  fraction = (double)(*pixelx - collarWx) / (double)mapw;
  distance = fraction * (double)(info.longW - info.longE);
  *longitude = (double)info.longW - distance;

  return (0);
}
