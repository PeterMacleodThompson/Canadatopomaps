/**
 * DOC: -- initmappath.c - finds mapset path based on country, usage
 * Peter Thompson 2020
 *
 * displays available country, usage and mapsets and then redirects thread to
 * country/usage/maps/ for execution of map navigation and downloading
 * Save mappath and countryusagecode for retrieval via
 *    getmappath()   and getcountryusagecode()
 *
 */

#define DATAPATH "/home/peter/bbb2020/oznext/data/share/oz3/"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char mappath[500];        /* path to maps */
static char countryusagecode[2]; /* countryusagecode */

int initmappath() {
  FILE *fp;
  DIR *d;
  struct dirent *dir;
  char save[20][50]; /* max 20 countries (or usages), 50 char long */
  char countrynow[50];
  char usagenow[50];
  char temp[250]; /* for countryusagecode */
  char inbuf[10];
  int i, ok;
  int choice;

  ok = 1;
  while (ok) {
    /* display available countries */
    printf("Available Countries\n");
    i = 0;
    strcpy(mappath, DATAPATH);
    d = opendir(mappath);
    while ((dir = readdir(d)) != NULL) {
      if (*dir->d_name == '.')
        continue;
      printf("%d) %s\n", i, dir->d_name);
      strcpy(save[i], dir->d_name); /* save country name */
      i++;
    }
    printf("select a country:");
    scanf("%d", &choice);
    if (choice < 0 || choice > i) {
      printf("invalid selection\n");
      continue;
    }
    strcpy(countrynow, save[choice]);
    printf("you selected %s\n", countrynow);
    closedir(d);

    /* display available usages */
    printf("Available Usages in %s\n", countrynow);

    i = 0;
    strcat(mappath, countrynow);
    d = opendir(mappath);
    while ((dir = readdir(d)) != NULL) {
      if (*dir->d_name == '.')
        continue;
      printf("%d) %s\n", i, dir->d_name);
      strcpy(save[i], dir->d_name); /* save country name */
      i++;
    }
    printf("select a usage:");
    scanf("%d", &choice);
    if (choice < 0 || choice > i) {
      printf("invalid selection\n");
      continue;
    }
    strcpy(usagenow, save[choice]);
    printf("you selected %s\n", usagenow);
    closedir(d);
    strcat(mappath, "/");
    strcat(mappath, usagenow);
    strcat(mappath, "/maps/");
    ok = 0;
  }

  /* get countryusagecode for return */
  strcpy(temp, mappath);
  strcat(temp, "countryusagecode");
  if ((fp = fopen(temp, "r")) == NULL) {
    printf("countryusagecode not found at %s\n", temp);
    return (-1);
  }
  if (fgets(inbuf, 5, fp) == NULL) {
    printf("countryusagecode empty %s\n", temp);
    return (-1);
  }
  countryusagecode[0] = inbuf[0];
  countryusagecode[1] = inbuf[1];
  return (0);
}

char *getcountryusagecode() { return (countryusagecode); }
char *getmappath() { return (mappath); }
