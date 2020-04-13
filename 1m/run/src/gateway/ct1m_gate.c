/**
 * DOC: -- ct1m_gate.c  -- gate functions for Canada/topographic/ 1:1000,000
 * maps Peter Thompson   -- March 2020
 *
 * ...gate.c redirects  oz3 map functions
 *       from - maphandler.c  (the double function pointers array)
 *       to   - Canada/topographic/maps/1m/run/src/ *.c
 *
 * ct1m_fillmapnow()
 * ct1m_gonorth()
 * ct1m_gosouth()
 * ct1m_goeast()
 * ct1m_gowest()
 * ct1m_gonorthqc()
 * ct1m_gosouthqc()
 * ct1m_goeastqc()
 * ct1m_gowestqc()
 * ct1m_zoomin()
 * ct1m_zoomout()
 * ct1m_zoominqc()
 * ct1m_zoomoutqc()
 * ct1m_download()
 * ct1m_display()
 * ct1m_collarcalc()
 * ct1m_collarshow()
 * ct1m_getmap()
 * ct1m_getmapinfo()
 * ct1m_setmap()
 * ct1m_lltopp()
 * ct1m_pptoll()
 * ct1m_fetmap()
 * ct1m_info()
 */

#include "display.h"
#include "maps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
void mapsetzoomin(void);
void mapsetzoomout(void);
int bsearch1m(char *);
char *getmappath(void);
char *find1mmap(double, double);
int ct_lltopp(double *, double *, int *, int *, mapindex);
int ct_pptoll(double *, double *, int *, int *, mapindex);

static char temp[500];
static mapindex info;

/**
 * fillmapnow() - given map index, fills in the rest of mapindex structure
 *   from mapindex file.
 * @ndx - new map index corresponding to new info.mapid
 * Assumption:   mapindex file is complete, sorted by mapid with associated
 * index.
 *    - indexes in mapindex do not change.
 * load current mapindex record from maps/1m/mapindex
 */

int ct1m_fillmapnow(int ndx) {
  FILE *fp;
  char *strptr1;
  char path[400];
  char inbuf[400];

  strptr1 = getmappath();
  strcpy(path, strptr1);
  strcat(path, "1m/mapindex");
  if ((fp = fopen(path, "r")) == NULL) {
    printf("file does not exist %s\n", path);
    return (-1);
  }
  while (fgets(inbuf, 400, fp) != NULL) {
    if (inbuf[0] == '#')
      continue;
    sscanf(inbuf,
           "%d %s %s %s %s %lf %lf %lf %lf %d %d %d %d %d %d %d %d %d %d %d %d "
           "%d %d",
           &info.index, info.mapid, info.desc, info.mapfilename,
           info.mapimagename, &info.latN, &info.longE, &info.latS, &info.longW,
           &info.pixelwidth, &info.pixelheight, &info.mapnorth, &info.mapeast,
           &info.mapsouth, &info.mapwest, &info.collarNEx, &info.collarNEy,
           &info.collarNWx, &info.collarNWy, &info.collarSEx, &info.collarSEy,
           &info.collarSWx, &info.collarSWy);
    if (info.index == ndx)
      break;
  }
  return (0);
}

/* 14 integer "nav" functions */
int ct1m_gonorth() {
  if (info.mapnorth <= 0)
    return (-1);
  else
    ct1m_fillmapnow(info.mapnorth);
  return (info.index);
}

int ct1m_gosouth() {
  if (info.mapsouth <= 0)
    return (-1);
  else
    ct1m_fillmapnow(info.mapsouth);
  return (info.index);
}

int ct1m_goeast() {
  if (info.mapeast <= 0)
    return (-1);
  else
    ct1m_fillmapnow(info.mapeast);
  return (info.index);
}

int ct1m_gowest() {
  if (info.mapwest <= 0)
    return (-1);
  else
    ct1m_fillmapnow(info.mapwest);
  return (info.index);
}

int ct1m_gonorthqc() {
  if (info.mapnorth < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}

int ct1m_gosouthqc() {
  if (info.mapsouth < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct1m_goeastqc() {
  if (info.mapeast < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct1m_gowestqc() {
  if (info.mapwest < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct1m_zoominqc() { return (1); }  /* TRUE map exists */
int ct1m_zoomoutqc() { return (0); } /* FALSE no map */
int ct1m_zoomin() {
  printf("ARRIVED at ct1m_zoomin\n");
  mapsetzoomin();
  return (1); /* return zoom factor zm */
}
int ct1m_zoomout() {
  printf("ARRIVED at ct1m_zoomout\n");
  mapsetzoomout();
  return (0);
}
int ct1m_download() {
  printf("%d %s already downloaded into maps/1m/ready/\n", info.index,
         info.mapid);
  printf("original map will be downloaded to maps/1m/raw/\n");
  printf(
      "All info is based on /1m/ready, /1m/mapindex, /1m/setup/mapindex.ods\n");
  printf("Must view /1m/raw/ manually\n");
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct1m_download\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "1m/raw/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "1m/run/scripts/downloadmap   ");
  strcat(scriptpath, info.mapfilename);
  strcat(scriptpath, "    ");
  strcat(scriptpath, savepath);
  printf("%s", scriptpath);
  system(scriptpath);
  return (0);
}

int ct1m_display() {
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct1m_display\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "1m/ready/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "1m/run/scripts/displaymap   ");
  strcat(scriptpath, savepath);
  strcat(scriptpath, info.mapid);
  printf("%s*", scriptpath);
  system(scriptpath);
  return (0);
}
int ct1m_collarcalc() {
  printf("All 1m maps ready - manually decollared\n");
  return (0);
}
int ct1m_collarshow() {
  printf("All 1m maps ready - no collar to show\n");
  return (0);
}

/* 2 character pointer "get" functions  */
char *ct1m_getmap() { return (info.mapid); }

char *ct1m_getmapinfo() {
  printf("ARRIVED at ct1m_getmapinfo\n");
  sprintf(
      temp,
      "%d %s %s %s %lf %lf %lf %lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
      info.index, info.mapid, info.mapfilename, info.mapimagename, info.latN,
      info.latS, info.longE, info.longW, info.pixelwidth, info.pixelheight,
      info.mapnorth, info.mapeast, info.mapsouth, info.mapwest, info.collarNEx,
      info.collarNEy, info.collarNWx, info.collarNWy, info.collarSEx,
      info.collarSEy, info.collarSWx, info.collarSWy);
  return (temp);
}

/* 3 integer "set" functions with 4 parameters */
int ct1m_setmap(double *latitude, double *longitude, int *c, int *d) {
  char *strptr;
  int exists;
  printf("ARRIVED at ct1m_setmap\n");
  strptr = find1mmap(*longitude, *latitude); /* returns calculated mapid */
  exists = bsearch1m(strptr);                /* check if mapid exists */
  if (exists < 0) {
    printf(" no map found at latitude %lf longitude %lf\n", *latitude,
           *longitude);
    return (-1);
  } else {
    ct1m_fillmapnow(exists);
  }
  return (1);
}

/* latlong to pixelpoint */
int ct1m_lltopp(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_lltopp(latitude, longitude, pixelx, pixely, info);
  return (err);
}
/* pixelpoint to latlong */
int ct1m_pptoll(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_pptoll(latitude, longitude, pixelx, pixely, info);
  return (err);
}

/* 1 integer "fet" (fetch) functions with 1 character parameter */
int ct1m_fetmap(char *mapid) {
  int exists;
  printf("ARRIVED at ct1m_fetchmap with %s\n", mapid);
  exists = bsearch1m(mapid); /* check if mapid exists */
  if (exists < 0) {
    printf(" map %s not found\n", mapid);
    return (-1);
  } else {
    strcpy(info.mapid, mapid);
    ct1m_fillmapnow(exists);
  }
  return (1);
}

/************  other functions ******************************/
mapindex *ct1m_info(void) { return (&info); }
