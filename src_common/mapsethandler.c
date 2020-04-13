/**
 * DOC: -- mapsethandler.c  -- zoomin, zoomout of different mapsets
 * Peter Thompson   -- 2019 Dec
 *
 * Returns 7 "mapset" values via 7 functions
 *   initmapset() returns pointer to array of mapsets
 *   initmapsetcnt() returns number of mapsets in array (via static int)
 *   mapsetnow() returns "now" pointer to current mapset info
 *   mapsetint() returns "now" index [i] to current mapset info
 *   mapsetzoomin()  increases "now" pointer and index to next mapset
 *   mapsetzoomout() decreases "now" pointer and index to previous mapset
 *   mapindexinfo()  returns pointer to "now" map info for current "now" mapset
 *
 */

#include "maps.h"
#include <errno.h> /* for strerror() */
#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <string.h>

#define TRUE 1
#define FALSE 0

/* function prototypes */
mapindex *ct1m_info(void);
mapindex *ct2k_info(void);
mapindex *ct5k_info(void);

static int mapsetcnt;
static mapset *mapsetptr;
static mapset *mapsetmax;
static mapset *mapsetmin;
static int maxzoom, zoom;

/**
 * initmapset()  load ~data/share/oz3/country/usage/maps/.mapset
 * file into memory
 * @*oldmapset existing country+usage mapset
 * @*datapath path to new country+usage mapset
 * returns new country+usage mapset o ../../bin/ringtestbased on
 * new datapath
 */
mapset *initmapset(mapset *oldmapset, char *datapath) {
  FILE *fp;
  char path[300];
  char inbuf[600];
  int first, i;
  mapset *newmapset;

  /*  load mapset location */
  strcpy(path, datapath);
  strcat(path, "mapsets");
  if ((fp = fopen(path, "r")) == NULL) {
    printf(" mapset file not found in %s\n", path);
    printf(" please create a file named mapset: %s\n", path);
    return (oldmapset);
  }
  /* remove old mapset space before o ../../bin/ringtestcreating new mapset
   * space */
  free(oldmapset);

  /* create new mapset array*/
  i = 0;
  first = TRUE;
  while (fgets(inbuf, 600, fp) != NULL) {
    if (inbuf[0] == '#')
      continue; /* skip records with # as 1st char */
    if (first) {
      newmapset = (mapset *)malloc(sizeof(mapset));
      first = FALSE;
    } else {
      newmapset = (mapset *)realloc(newmapset, (i + 1) * sizeof(mapset));
      if (newmapset == NULL) {
        printf("realloc error: %s\n", strerror(errno));
        return (NULL);
      }
    }
    sscanf(inbuf, "%s %s %s %d %d %d %d %d %d", (newmapset + i)->name,
           (newmapset + i)->urlpublic, (newmapset + i)->urlpmt,
           &(newmapset + i)->kscale, &(newmapset + i)->collarN,
           &(newmapset + i)->collarS, &(newmapset + i)->collarE,
           &(newmapset + i)->collarW, &(newmapset + i)->noblack);
    printf("%d mapsetname = %s address = %p\n", i, (newmapset + i)->name,
           newmapset + i);
    i++;
  }
  mapsetcnt = i; /* return count in separate function */
  maxzoom = i - 1;
  zoom = 0;
  mapsetmax = newmapset + (i - 1);
  mapsetmin = newmapset;
  mapsetptr = newmapset;
  return (newmapset);
}

/**
 * initmapsetcnt()
 * return count of mapsets for this country/usage
 */
int initmapsetcnt(void) { return (mapsetcnt); }

/**
 * mapsetnow()
 * return pointer to "now" mapset information
 */
mapset *mapsetnow() { /* zm = zoom factor */
  return (mapsetptr);
}

/**
 * mapsetint()
 * return index for "now" mapset in mapset info array
 */
int mapsetint() { return (zoom); }

/**
 * mapsetzoomin()
 * increment pointer and index for "now" mapset
 */
void mapsetzoomin(void) {
  if (mapsetptr < mapsetmax && zoom < maxzoom) {
    mapsetptr++;
    zoom++;
  }
  return;
}

/**
 * mapsetzoomout()
 * decrement pointer and index for "now" mapset
 */
void mapsetzoomout(void) {
  if (mapsetptr > mapsetmin && zoom > 0) {
    mapsetptr--;
    zoom--;
  }
  return;
}

/**
 * mapindexinfo()
 * given current "now" mapset, return "now" map info pointer
 */
mapindex *mapindexinfo(void) {
  if (zoom == 0)
    return (ct1m_info()); /* 1m mapnow index info */
  else if (zoom == 1)
    return (ct2k_info());
  else if (zoom == 2)
    return (ct5k_info());
  return (NULL); /* error in zoom */
}
