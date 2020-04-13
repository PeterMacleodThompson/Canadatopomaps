/**
 * DOC: -- ct5k_mapE.c -- find adjacent map to east
 * Peter Thompson 2020
 *
 * maps are 4x4 matrix labelled 1,2,3...15,16
 * starting at [0][0], to get next mapid east
 *   even rows [0] and [2]  ==> subtract 1
 *   odd rows [1] and [3]   ==> add 1
 */
#define EVEN 0
#define ODD 1

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch50k(char *);
int bsearch250k(char *); /* FIXME */
void northpoleS(char *); /* FIXME */
void farnorthS(char *);  /* FIXME */
int mapE(char *);

/**
 * mapE() - find adjacent map to east
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map east
 *         NULL if no such map exists
 */
int ct5k_mapE(char mapid[]) {
  int x, z;
  int digit10, digit1;
  int exists;
  int east;
  char save[7];
  char mapid250[7];

  strcpy(save, mapid); /* save mapid */
  strcpy(mapid250, mapid);
  mapid250[4] = '\0'; /* save 250k version of mapid */

  /* Normal Canada handling */
  digit1 = mapid[5] - '0'; /* convert char to digit */
  digit10 = mapid[4] - '0';
  x = (digit10 * 10) + digit1; /* integers 1,2,...15,16 */

  /* check if in right column, need new 250k map */
  if (x == 1 || x == 8 || x == 9 || x == 16) {
    exists = mapE(mapid250); /* changes info.mapid to new mapid */
    if (exists < 0) {
      printf(" nothing found in 250k maps east of %s, map unchanged", mapid250);
      return (-1);
    }
    if (x == 8 || x == 16) /* reset map from right to left column*/
      x = x - 3;
    else
      x = x + 3;
    strcpy(mapid, mapid250); /* copy new 250k map into 50k map */
  } else {                   /* ok to go east within 250k map */
    z = (x - 1) / 4 % 2;     /* even row or odd row */
    if (z == EVEN)
      x--;
    else if (z == ODD)
      x++;
  }

  /* integer to ascii for map 50k extension */
  mapid[5] = '0' + x % 10;
  mapid[4] = '0' + x / 10;

  east = bsearch50k(mapid);
  if (east < 0)
    strcpy(mapid, save); /* restore mapid */

  return (east);
}
