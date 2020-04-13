/* mainfortesting.c  - /Canada/topographic/
 * Peter Thompson March 2020
 * compile with: makefile
 */

#include "maps.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function prototypes */
int mapinit(char *);

int download();
int display();
int gonorth();
int gosouth();
int goeast();
int gowest();
int gonorthqc();
int gosouthqc();
int goeastqc();
int gowestqc();
int zoominqc();
int zoomoutqc();
int zoomin();
int zoomout();
int collarcalc();
int collarshow();

char *getmap();
char *getmapinfo();

int setmap(double *, double *, int *, int *);
int lltopp(double *, double *, int *, int *); /* latlong to pixelpoint */
int pptoll(double *, double *, int *, int *); /* pixelpoint to latlong */

int fetchmap(char *);

char *getcountryusagecode(void);
int initmappath(void);
char *getmappath();
mapset *mapsetnow(void);
void mapclose();

int main() {
  mapindex info;          /* for getmapinfo() */
  char *mapinfo;          /* for getmapinfo() */
  char *countryusagecode; /* country/usage code - 2 char */
  int quit, err, zero;
  char c, d;
  char inbuf[20];
  double longitude, latitude;
  int pixelx, pixely;
  int zoomfactor;
  char *mapid;
  char string[50];
  mapset *mapsetp;

  err = -1;
  while (err < 0) {
    err = initmappath();
    if (err < 0) {
      printf("no countryusage code found, try again\n");
      continue;
    }
    countryusagecode = getcountryusagecode();
    err = mapinit(countryusagecode); /* init functions for countryusagecode */
    if (err < 0) {
      printf(" function initialization failed for %s\n", getmappath());
      exit(1);
    }
  }
  printf("functions & maps successfully initiated for\n %s\n", getmappath());

  zoomfactor = 0; /* default */
  quit = 0;
  while (quit == 0) {
    printf("\n 1) Find new map via longitude, latitude\n");
    printf(" 2) Show current map info\n");
    printf(" 3) Download current map\n");
    printf(" 4) Display current map\n");
    printf(" 5) Move 1 map North\n");
    printf(" 6) Move 1 map South\n");
    printf(" 7) Move 1 map East\n");
    printf(" 8) Move 1 map West\n");
    printf(" 9) Zoom in 1 mapset\n");
    printf(" a) Zoom out 1 mapset\n");
    printf(" b) Compute collars for current map\n");
    printf(" c) Show collars for current map\n");
    printf(" d) Show current mapid\n");
    printf(" e) Find new map via mapid\n");
    printf(" f) View mapset info\n");
    printf(" g) long lat to pixel position on current map\n");
    printf(" h) pixel position to long lat on current map\n");
    printf(" x) Exit\n");
    printf("    What would you like to do ?");
    c = getchar();
    while ((d = getchar()) != '\n' && d != EOF) {
    } /* fflush(stdin); */

    if (c == '1') {
      printf("POPULAR LATITUDE, LONGITUDE LOCATIONS\n");
      printf("Calgary = 51.047, 114.0719;  Pano =  50,4604, 116.23\n");
      printf(
          "Percy Lake = 45.2191, 78.3697 ;  Ucluelet =  48.9416, 125.5463\n");
      printf(
          "Foster Lakes = 56.5500, 105.3833,; nahanni = 61.6081, 125.7357, \n");
      printf("Yellowknife = 62.4540, 114.37, Alert = 82.5018, 62.3418; Old "
             "Crow = 67.5696, 139.8288\n\n");
      printf("Enter latitude, longitude as ddd.dddd ddd.dddd:");
      fgets(inbuf, sizeof(inbuf), stdin);
      err = sscanf(inbuf, "%lf %lf", &latitude, &longitude);
      if (err == EOF)
        break;
      zero = 0;
      err = setmap(&latitude, &longitude, &zero, &zero);
      printf("err return = %d\n", err);
      printf("Success! - new map found! \n");
    }

    if (c == '2') {
      mapinfo = getmapinfo();
      printf("mapinfo = %s\n", mapinfo);
      sscanf(mapinfo,
             "%d %s %s %s %lf %lf %lf %lf %d %d %d %d %d %d %d %d %d %d %d %d "
             "%d %d",
             &info.index, info.mapid, info.mapfilename, info.mapimagename,
             &info.latN, &info.latS, &info.longE, &info.longW, &info.pixelwidth,
             &info.pixelheight, &info.mapnorth, &info.mapeast, &info.mapsouth,
             &info.mapwest, &info.collarNEx, &info.collarNEy, &info.collarNWx,
             &info.collarNWy, &info.collarSEx, &info.collarSEy, &info.collarSWx,
             &info.collarSWy);
      printf("\n\n\nCurrent Map in mapset %d:\n mapid = %s, mapindex = %d\n ",
             zoomfactor, info.mapid, info.index);
      printf("mapfilename = %s\n mapimagename = %s\n", info.mapfilename,
             info.mapimagename);
      printf("LatN = %lf, LatS = %lf\nLongE = %lf, LongW = %lf\n", info.latN,
             info.latS, info.longE, info.longW);
      printf("pixel: width = %d, height = %d degrees/pixel  w = %lf h=%lf\n",
             info.pixelwidth, info.pixelheight,
             (info.longW - info.longE) / info.pixelwidth,
             (info.latN - info.latS) / info.pixelheight);
      printf("Adjacent maps: North %d, East %d, South %d, West %d\n",
             info.mapnorth, info.mapeast, info.mapsouth, info.mapwest);
      printf("Collar North edge %d %d\n", info.collarNWy, info.collarNEy);
      printf("Collar South edge %d %d\n", info.collarSWy, info.collarSEy);
      printf("Collar West edge %d %d\n", info.collarNWx, info.collarSWx);
      printf("Collar East edge %d %d\n", info.collarNEx, info.collarSEx);
    }

    if (c == '3') {
      err = download();
      printf("err return = %d\n", err);
    }
    if (c == '4') {
      err = display();
      printf("err return = %d\n", err);
    }
    if (c == '5') {
      err = gonorth();
      if (err > 0)
        printf("New map index = %d\n", err);
      else
        printf("no map exists to north\n");
    }
    if (c == '6') {
      err = gosouth();
      if (err > 0)
        printf("New map index = %d\n", err);
      else
        printf("no map exists to south\n");
    }
    if (c == '7') {
      err = goeast();
      if (err > 0)
        printf("New map index = %d\n", err);
      else
        printf("no map exists to east\n");
    }
    if (c == '8') {
      err = gowest();
      if (err > 0)
        printf("New map index = %d\n", err);
      else
        printf("no map exists to west\n");
    }
    if (c == '9') {
      printf("OLD mapset is %d\n", zoomfactor);
      zoomfactor = zoomin();
      printf("NEW mapset is %d\n", zoomfactor);
    }
    if (c == 'a') {
      printf("OLD mapset is %d\n", zoomfactor);
      zoomfactor = zoomout();
      printf("NEW mapset is %d\n", zoomfactor);
    }
    if (c == 'b') {
      err = collarcalc();
      printf("return code = %d\n", err);
    }
    if (c == 'c') {
      err = collarshow();
      printf("return code = %d\n", err);
    }

    if (c == 'd') {
      mapid = getmap();
      printf(" mapid = %s\n", mapid);
    }

    if (c == 'e') {
      printf("Enter mapid to fetch:");
      fgets(inbuf, sizeof(inbuf), stdin);
      err = sscanf(inbuf, "%s", string);
      printf("you entered %s\n", string);
      if (err == EOF)
        break;
      fetchmap(string);
    }
    if (c == 'f') {
      mapsetp = mapsetnow();
      printf("mapset = %s\n  url=%s\n  kscale=%d\n", mapsetp->name,
             mapsetp->urlpublic, mapsetp->kscale);
      printf("  collars(N,S,E,W) = %d  %d  %d  %d\n", mapsetp->collarN,
             mapsetp->collarS, mapsetp->collarE, mapsetp->collarW);
      printf("grayscale threshold 0-255 converted to white=255 ==> %d\n",
             mapsetp->noblack);
    }

    if (c == 'g') {
      printf("POPULAR LATITUDE, LONGITUDE LOCATIONS\n");
      printf("Calgary = 51.047, 114.0719;  Pano =  50,4604, 116.23\n");
      printf(
          "Percy Lake = 45.2191, 78.3697 ;  Ucluelet =  48.9416, 125.5463\n");
      printf(
          "Foster Lakes = 56.5500, 105.3833,; nahanni = 61.6081, 125.7357, \n");
      printf("Yellowknife = 62.4540, 114.37, Alert = 82.5018, 62.3418; Old "
             "Crow = 67.5696, 139.8288\n\n");
      printf("Enter latitude, longitude as ddd.dddd ddd.dddd:");
      fgets(inbuf, sizeof(inbuf), stdin);
      err = sscanf(inbuf, "%lf %lf", &latitude, &longitude);
      if (err == EOF)
        break;
      lltopp(&latitude, &longitude, &pixelx, &pixely);
      printf("latitude=%lf, longitude=%lf, pixelx=%d, pixely=%d\n", latitude,
             longitude, pixelx, pixely);
    }

    if (c == 'h') {
      printf("Enter pixelx   pixely in current map:");
      fgets(inbuf, sizeof(inbuf), stdin);
      err = sscanf(inbuf, "%d %d", &pixelx, &pixely);
      if (err == EOF)
        break;
      pptoll(&latitude, &longitude, &pixelx, &pixely);
      printf("latitude=%lf, longitude=%lf, pixelx=%d, pixely=%d\n", latitude,
             longitude, pixelx, pixely);
    }

    if (c == 'x') {
      mapclose();
      exit(0);
    }
  }
}
