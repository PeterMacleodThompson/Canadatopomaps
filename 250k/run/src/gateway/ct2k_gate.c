/**
 * DOC: -- ct2k_gate.c  -- gate functions for Canada/topographic/ 1:250,000
 * maps Peter Thompson   -- March 2020
 *
 * ...gate.c redirects  oz3 map functions
 *       from - maphandler.c  (the double function pointers array)
 *       to   - Canada/topographic/maps/250k/run/src/  *.c
 *
 * ct2k_fillmapnow()
 * ct2k_gonorth()
 * ct2k_gosouth()
 * ct2k_goeast()
 * ct2k_gowest()
 * ct2k_gonorthqc()
 * ct2k_gosouthqc()
 * ct2k_goeastqc()
 * ct2k_gowestqc()
 * ct2k_zoomin()
 * ct2k_zoomout()
 * ct2k_zoominqc()
 * ct2k_zoomoutqc()
 * ct2k_download()
 * ct2k_display()
 * ct2k_collarcalc()
 * ct2k_collarshow()
 * ct2k_getmap()
 * ct2k_getmapinfo()
 * ct2k_setmap()
 * ct2k_lltopp()
 * ct2k_pptoll()
 * ct2k_fetmap()
 * ct2k_info()
 */

#include "display.h"
#include "maps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
char *getmappath(void);
double latN(char *);
double latS(char *);
double longE(char *);
double longW(char *);
int mapN(char *);
int mapS(char *);
int mapE(char *);
int mapW(char *);
int bsearch250k(char *);
char *lsearch250k(char *, char *);
char *find250kmap(double, double);
int ct_collarcalc(void);
int ct_collarmark(void);
void mapsetzoomin(void);
void mapsetzoomout(void);
int ct_lltopp(double *, double *, int *, int *, mapindex);
int ct_pptoll(double *, double *, int *, int *, mapindex);

char temp[500];
static mapindex info;
void freearray(void);

/**
 * fillmapindex() - given new info.mapid, fills in the rest of mapindex
 * structure
 * @ndx - new map index corresponding to new info.mapid
 *   used when new mapid located and placed in info.mapid
 */
void fillmapindex(int ndx) {
  char *strptr1, *strptr2;
  char path[400];

  info.index = ndx; /* info.mapid already changed */
  strptr1 = getmappath();
  strcpy(path, strptr1);
  strcat(path, "250k/maplist");
  strptr2 = lsearch250k(info.mapid, path);
  if (strptr2 == NULL)
    exit(0);
  strcpy(info.mapfilename, strptr2);

  strcpy(path, strptr1);
  strcat(path, "250k/mapimages");
  strptr2 = lsearch250k(info.mapid, path);
  if (strptr2 == NULL)
    exit(0);
  strcpy(info.mapimagename, strptr2);

  info.latN = latN(info.mapid);
  info.latS = latS(info.mapid);
  info.longE = longE(info.mapid);
  info.longW = longW(info.mapid);
}

/* 16 integer "nav" functions */
int ct2k_gonorth() {
  int exists;
  printf("ARRIVED at ct2k_gonorth\n");
  exists = mapN(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found North of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    fillmapindex(exists);
  }
  return (exists);
}
int ct2k_gosouth() {
  int exists;
  printf("ARRIVED at ct2k_gosouth\n");
  exists = mapS(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found South of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    fillmapindex(exists);
  }
  return (exists);
}
int ct2k_goeast() {
  int exists;
  printf("ARRIVED at ct2k_goeast\n");
  exists = mapE(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found East of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    fillmapindex(exists);
  }
  return (exists);
}
int ct2k_gowest() {
  int exists;
  printf("ARRIVED at ct2k_gowest\n");
  exists = mapW(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found West of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    fillmapindex(exists);
  }
  return (exists);
}

int ct2k_gonorthqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = mapN(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct2k_gosouthqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = mapS(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct2k_goeastqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = mapE(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct2k_gowestqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = mapW(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct2k_zoominqc() { return (1); }  /* TRUE map exists */
int ct2k_zoomoutqc() { return (1); } /* TRUE map exists */
int ct2k_zoomin() {
  printf("ARRIVED at ct2k_zoomin\n");
  mapsetzoomin();
  return (2);
}
int ct2k_zoomout() {
  printf("ARRIVED at ct2k_zoomout\n");
  mapsetzoomout();
  return (0);
}

int ct2k_download() {
  char scriptpath[500];
  char savepath[200];
  SDL_Surface *image;

  printf("ARRIVED at ct2k_download\n");
  /* script format: "downloadmap  filename  savelocation" */
  strcpy(savepath, getmappath());
  strcat(savepath, "250k/raw/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "250k/run/scripts/downloadmap   ");
  strcat(scriptpath, info.mapfilename);
  strcat(scriptpath, "    ");
  strcat(scriptpath, savepath);
  printf("%s", scriptpath);
  system(scriptpath);

  /* update mapindex with pixel width, height */
  strcat(savepath, info.mapimagename);
  image = IMG_Load(savepath);
  if (image == NULL) {
    printf(" file not exist %s\n", savepath);
    return (-1);
  }
  info.pixelwidth = image->w;
  info.pixelheight = image->h;
  SDL_FreeSurface(image);
  return (0);
}

int ct2k_display() {
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct2k_display\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "250k/raw/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "250k/run/scripts/displaymap   ");
  strcat(scriptpath, savepath);
  strcat(scriptpath, info.mapid);
  printf("%s*", scriptpath);
  system(scriptpath);
  return (2015);
}
int ct2k_collarcalc() {
  int temp;
  printf("ARRIVED at ct2k_collarcalc\n");
  temp = ct_collarcalc();
  temp = ct_collarmark();
  freearray(); /* finished with array for now */
  return (temp);
}
int ct2k_collarshow() {
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct2k_collarshow\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "250k/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "250k/run/scripts/showcollar   ");
  strcat(scriptpath, savepath);
  system(scriptpath);
  return (0);
}

/* 2 character pointer "get" functions  */
char *ct2k_getmap() { return (info.mapid); }

char *ct2k_getmapinfo() {
  printf("ARRIVED at ct2k_getmapinfo\n");
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
int ct2k_setmap(double *latitude, double *longitude, int *c, int *d) {
  char *strptr;
  int exists;
  printf("ARRIVED at ct2k_setmap\n");
  strptr = find250kmap(*longitude, *latitude); /* returns calculated mapid */
  exists = bsearch250k(strptr);                /* check if mapid exists */
  if (exists < 0) {
    printf(" no map found at latitude %lf longitude %lf\n", *latitude,
           *longitude);
    return (-1);
  } else {
    strcpy(info.mapid, strptr);
    fillmapindex(exists);
  }
  return (1);
}

/* latlong to pixelpoint */
int ct2k_lltopp(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_lltopp(latitude, longitude, pixelx, pixely, info);
  return (err);
}
/* pixelpoint to latlong */
int ct2k_pptoll(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_pptoll(latitude, longitude, pixelx, pixely, info);
  return (err);
}

/* 1 integer "fet" (fetch) functions with 1 character parameter */
int ct2k_fetmap(char *mapid) {
  int exists;
  printf("ARRIVED at ct2k_fetchmap\n");
  exists = bsearch250k(mapid); /* check if mapid exists */
  if (exists < 0) {
    printf(" map %s not found\n", mapid);
    return (-1);
  } else {
    strcpy(info.mapid, mapid);
    fillmapindex(exists);
  }
  return (1);
}

/************  other functions ******************************/
mapindex *ct2k_info(void) { return (&info); }
