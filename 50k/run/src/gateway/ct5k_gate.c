/**
 * DOC: -- ct5k_gate.c  -- gate functions for Canada/topographic/ 1:50,000
 * maps Peter Thompson   -- March 2020
 *
 * ...gate.c redirects  oz3 map functions
 *       from - maphandler.c  (the double function pointers array)
 *       to   - Canada/topographic/maps/50k/run/src/ *.c
 *
 * ct5k_fillmapnow()
 * ct5k_gonorth()
 * ct5k_gosouth()
 * ct5k_goeast()
 * ct5k_gowest()
 * ct5k_gonorthqc()
 * ct5k_gosouthqc()
 * ct5k_goeastqc()
 * ct5k_gowestqc()
 * ct5k_zoomin()
 * ct5k_zoomout()
 * ct5k_zoominqc()
 * ct5k_zoomoutqc()
 * ct5k_download()
 * ct5k_display()
 * ct5k_collarcalc()
 * ct5k_collarshow()
 * ct5k_getmap()
 * ct5k_getmapinfo()
 * ct5k_setmap()
 * ct5k_lltopp()
 * ct5k_pptoll()
 * ct5k_fetmap()
 * ct5k_info()
 */

#include "display.h"
#include "maps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
void mapsetzoomin(void);
void mapsetzoomout(void);
char *lsearch50k(char *, char *);
int bsearch50k(char *);
char *getmappath(void);
double ct5k_latN(char *);
double ct5k_latS(char *);
double ct5k_longE(char *);
double ct5k_longW(char *);
char *find250kmap(double, double);
char *find50kmap(double, double);
int ct5k_mapN(char *);
int ct5k_mapS(char *);
int ct5k_mapE(char *);
int ct5k_mapW(char *);
int ct_collarcalc(void);
int ct_collarmark(void);
int ct_lltopp(double *, double *, int *, int *, mapindex);
int ct_pptoll(double *, double *, int *, int *, mapindex);

static char temp[500];
static mapindex info;
void freearray(void);

/**
 * fillmapindex() - given new info.mapid, fills in the rest of mapindex
 * structure
 * @ndx - new map index corresponding to new info.mapid
 *   used when new mapid located and placed in info.mapid
 */
void ct5k_fillmapindex(int ndx) {
  char *strptr1, *strptr2;
  char path[400];

  info.index = ndx; /* info.mapid already changed */
  strptr1 = getmappath();
  strcpy(path, strptr1);
  strcat(path, "50k/maplist");
  strptr2 = lsearch50k(info.mapid, path);
  if (strptr2 == NULL)
    exit(0);
  strcpy(info.mapfilename, strptr2);

  strcpy(path, strptr1);
  strcat(path, "50k/mapimages");
  strptr2 = lsearch50k(info.mapid, path);
  if (strptr2 == NULL)
    exit(0);
  strcpy(info.mapimagename, strptr2);

  info.latN = ct5k_latN(info.mapid);
  info.latS = ct5k_latS(info.mapid);
  info.longE = ct5k_longE(info.mapid);
  info.longW = ct5k_longW(info.mapid);
}

/* 16 integer "nav" functions */
int ct5k_gonorth() {
  int exists;
  printf("ARRIVED at ct5k_gonorth\n");
  exists = ct5k_mapN(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found North of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    ct5k_fillmapindex(exists);
  }
  return (exists);
}

int ct5k_gosouth() {
  int exists;
  printf("ARRIVED at ct5k_gosouth\n");
  exists = ct5k_mapS(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found South of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    ct5k_fillmapindex(exists);
  }
  return (exists);
}

int ct5k_goeast() {
  int exists;
  printf("ARRIVED at ct5k_goeast\n");
  exists = ct5k_mapE(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found East of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    ct5k_fillmapindex(exists);
  }
  return (exists);
}

int ct5k_gowest() {
  int exists;
  printf("ARRIVED at ct5k_gowest\n");
  exists = ct5k_mapW(info.mapid); /* changes info.mapid to new mapid */
  if (exists < 0) {
    printf(" nothing found West of %s, map unchanged", info.mapid);
    return (-1);
  } else {
    ct5k_fillmapindex(exists);
  }
  return (exists);
}

int ct5k_gonorthqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = ct5k_mapN(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct5k_gosouthqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = ct5k_mapS(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct5k_goeastqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = ct5k_mapE(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct5k_gowestqc() {
  int exists;
  char temp[10];
  strcpy(temp, info.mapid);
  exists = ct5k_mapW(temp); /* changes temp to new mapid */
  if (exists < 0)
    return (0); /* FALSE */
  else
    return (1); /* TRUE */
}
int ct5k_zoominqc() { return (0); }  /* FALSE no map */
int ct5k_zoomoutqc() { return (1); } /* TRUE map exists */
int ct5k_zoomin() {
  printf("ARRIVED at ct5k_zoomin\n");
  mapsetzoomin();
  return (2);
}
int ct5k_zoomout() {
  printf("ARRIVED at ct5k_zoomout\n");
  mapsetzoomout();
  return (1);
}

int ct5k_download() {
  char scriptpath[500];
  char savepath[200];
  SDL_Surface *image;

  printf("ARRIVED at ct5k_download\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "50k/raw/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "50k/run/scripts/downloadmap   ");
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

int ct5k_display() {
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct5k_display\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "50k/raw/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "50k/run/scripts/displaymap   ");
  strcat(scriptpath, savepath);
  strcat(scriptpath, info.mapid);
  printf("%s*", scriptpath);
  system(scriptpath);
  return (3015);
}

int ct5k_collarcalc() {
  int temp;
  printf("ARRIVED at ct5k_collarcalc\n");
  temp = ct_collarcalc();
  temp = ct_collarmark();
  freearray(); /* finished with array for now */
  return (temp);
}

int ct5k_collarshow() {
  char scriptpath[500];
  char savepath[200];
  printf("ARRIVED at ct5k_collarshow\n");
  strcpy(savepath, getmappath());
  strcat(savepath, "50k/");
  strcpy(scriptpath, getmappath());
  strcat(scriptpath, "50k/run/scripts/showcollar   ");
  strcat(scriptpath, savepath);
  system(scriptpath);
  return (0);
}

/* 2 character pointer "get" functions  */
char *ct5k_getmap() { return (info.mapid); }

char *ct5k_getmapinfo() {
  printf("ARRIVED at ct5k_getmapinfo\n");
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
int ct5k_setmap(double *latitude, double *longitude, int *c, int *d) {
  char *strptr1;
  char *strptr2;
  int exists;
  printf("ARRIVED at ct5k_setmap\n");
  strptr1 = find250kmap(*longitude,
                        *latitude); /* returns calculated mapid for 250k */
  strptr2 = find50kmap(*longitude, *latitude);

  strcat(strptr1, strptr2);
  exists = bsearch50k(strptr1); /* check if mapid exists */
  if (exists < 0) {
    printf(" no map found at latitude %lf longitude %lf\n", *latitude,
           *longitude);
    return (-1);
  } else {
    strcpy(info.mapid, strptr1);
    ct5k_fillmapindex(exists);
  }
  return (1);
}
/* latlong to pixelpoint */
int ct5k_lltopp(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_lltopp(latitude, longitude, pixelx, pixely, info);
  return (err);
}
/* pixelpoint to latlong */
int ct5k_pptoll(double *latitude, double *longitude, int *pixelx, int *pixely) {
  int err;
  err = ct_pptoll(latitude, longitude, pixelx, pixely, info);
  return (err);
}

/* 1 integer "fet" (fetch) functions with 1 character parameter */
int ct5k_fetmap(char *mapid) {
  int exists;
  printf("ARRIVED at ct5k_fetchmap\n");
  exists = bsearch50k(mapid); /* check if mapid exists */
  if (exists < 0) {
    printf(" map %s not found\n", mapid);
    return (-1);
  } else {
    strcpy(info.mapid, mapid);
    ct5k_fillmapindex(exists);
  }
  return (1);
}

/************  other functions ******************************/
mapindex *ct5k_info(void) { return (&info); }
