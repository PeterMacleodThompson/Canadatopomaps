/**
 * DOC: -- lsearch.c -- find filename in maplist based on mapid
 * Peter Thompson 2020
 *
 * linear search of maplist file based on mapid = 1st 4 char of maplist
 */

#include <stdio.h>
#include <string.h>

/**
 * lsearch1m() - linear search of maplist file
 * assumes
 *    maplist is sorted,
 *    mapid is 1st 4 char,
 *    mapid is unique
 *
 * return: map filename in maplist
 */
char *lsearch1m(char mapid[], char *filename) {
  static char mapfilename[200];
  char inbuf[200];
  FILE *fp;
  int cnt, len;

  if ((fp = fopen(filename, "r")) == NULL) {
    printf("file does not exist %s\n", filename);
    return (NULL);
  }
  cnt = 0;
  while (fgets(inbuf, 200, fp) != NULL) {
    if (mapid[0] == inbuf[0] && mapid[1] == inbuf[1] && mapid[2] == inbuf[2] &&
        mapid[3] == inbuf[3]) {
      len = strlen(inbuf);
      if (inbuf[len - 1] == '\n') /* remove trailing \n in inbuf */
        inbuf[len - 1] = '\0';
      strcpy(mapfilename, inbuf);
      return (mapfilename);
    }
    cnt++; /* next record */
  }
  cnt++;
  printf("no match found in %d records\n", cnt);
  return (NULL);
}
