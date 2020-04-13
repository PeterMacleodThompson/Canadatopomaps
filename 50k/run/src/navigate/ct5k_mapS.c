/**
 * DOC: -- ct5k_mapS.c -- find adjacent map to South
 * Peter Thompson 2020
 *
 * maps are 4x4 matrix labelled 1,2,3...15,16
 * and organized spatially as follows:
 *      13   14    15   16
 *      12   11    10    9
 *       5    6     7    8
 *       4    3     2    1
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch50k(char *);
int bsearch250k(char *); /* FIXME */
void northpoleS(char *); /* FIXME */
void farnorthS(char *);  /* FIXME */
int mapS(char *);

/**
 * mapS() - find adjacent map to south
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map south
 *         NULL if no such map exists
 */
int ct5k_mapS(char mapid[]) {
  int x, z;
  int digit10, digit1;
  int exists;
  int south;
  char save[7];
  char mapid250[7];

  strcpy(save, mapid); /* save mapid */
  strcpy(mapid250, mapid);
  mapid250[4] = '\0'; /* save 250k version of mapid */

  /* Normal Canada handling */
  digit1 = mapid[5] - '0'; /* convert char to digit */
  digit10 = mapid[4] - '0';
  x = (digit10 * 10) + digit1; /* integers 1,2,...15,16 */

  if (x < 5) {               /* in bottom row, need new 250k map */
    exists = mapS(mapid250); /* changes info.mapid to new mapid */
    if (exists < 0) {
      printf(" nothing found in 250k maps South of %s, map unchanged",
             mapid250);
      return (-1);
    }
    x = 17 - x;              /* reset map to top row */
    strcpy(mapid, mapid250); /* copy new 250k map into 50k map */
  } else {                   /* go south within 250k map */
    z = x % 4;
    if (z == 0)
      x -= 7;
    else if (z == 1)
      x -= 1;
    else if (z == 2)
      x -= 3;
    else if (z == 3)
      x -= 5;
  }

  /* integer to ascii for map 50k extension */
  mapid[5] = '0' + x % 10;
  mapid[4] = '0' + x / 10;

  south = bsearch50k(mapid);
  if (south < 0)
    strcpy(mapid, save); /* restore mapid */

  return (south);
}
