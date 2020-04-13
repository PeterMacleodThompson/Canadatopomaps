/**
 * DOC: -- validate250k.c -- validate if 250k map exists on public url
 * Peter Thompson 2020
 *
 * init50k() builds array of 4 char mapid's from maplist
 * bsearch50k()  binary search of the array
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

static char mapvector[1000][5];
static int mapcnt;

/* function prototypes */
char *getmappath(void);

/**
 * init250k() - build maplist of c250k maps
 * assumes
 *    maplist is sorted,
 *    mapid is 1st 4 char,
 *    mapid is unique
 * sets static variables: mapvector, mapcnt
 * return:
 */
int init250k() {
  char inbuf[200];
  FILE *fp;
  int cnt, i;
  char *temp;
  char path[400];

  temp = getmappath();
  strcpy(path, temp);
  strcat(path, "250k/maplist");
  if ((fp = fopen(path, "r")) == NULL) {
    printf("maplist file does not exist %s\n", path);
    return (-1);
  }
  cnt = 0;
  while (fgets(inbuf, 200, fp) != NULL) {
    for (i = 0; i < 4; i++) /* mapid is 1st 4 char */
      mapvector[cnt][i] = inbuf[i];
    mapvector[cnt][4] = '\0'; /* string*/
    cnt++;                    /* next record */
  }
  mapcnt = cnt + 1;
  printf("finished %d records\n", mapcnt);
  return (0);
}

/**
 * bsearch250k() - standard binary search
 * @string: mapid
 * return:  index of mapid OR -1 if not found
 */
int bsearch250k(char *string) {
  int bottom = 0;
  int mid;
  int top;
  int eq;

  top = mapcnt - 1;
  while (bottom <= top) {
    mid = (bottom + top) / 2;
    eq = strcmp(mapvector[mid], string);
    if (eq == 0) {
      /*          printf("%s found at location %d.\n", string, mid+1); */
      return (mid + 1);
    } else if (eq > 0)
      top = mid - 1;
    else if (eq < 0)
      bottom = mid + 1;
  }
  return (-1);
}
