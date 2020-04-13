/**
 * DOC: -- mapS.c -- find adjacent map to South
 * Peter Thompson 2020
 *
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch250k(char *);
void northpoleS(char *);
void farnorthS(char *);

/**
 * mapS() - find adjacent map to South
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map south
 *         NULL if no such map exists
 */
int mapS(char mapid[]) {
  int south;
  char save[7];

  strcpy(save, mapid); /* save mapid */

  /* North Pole exception handling */
  if (mapid[0] > '1' || (mapid[0] == '1' && mapid[1] == '2')) {
    northpoleS(mapid);
    south = bsearch250k(mapid);
    if (south < 0)
      strcpy(mapid, save); /* restore mapid */
    return (south);
  }

  /*  Far North exception handling */
  if (mapid[2] > '6') {
    farnorthS(mapid);
    south = bsearch250k(mapid);
    if (south < 0)
      strcpy(mapid, save); /* restore mapid */
    return (south);
  }

  /* convert filename to filename adjacent south for rest of Canada */
  if (mapid[3] == 'a') {
    mapid[3] = 'p';
    mapid[2]--;
  } else if (mapid[3] == 'b') {
    mapid[3] = 'o';
    mapid[2]--;
  } else if (mapid[3] == 'c') {
    mapid[3] = 'n';
    mapid[2]--;
  } else if (mapid[3] == 'd') {
    mapid[3] = 'm';
    mapid[2]--;
  } else if (mapid[3] == 'e')
    mapid[3] = 'd';
  else if (mapid[3] == 'f')
    mapid[3] = 'c';
  else if (mapid[3] == 'g')
    mapid[3] = 'b';
  else if (mapid[3] == 'h')
    mapid[3] = 'a';
  else if (mapid[3] == 'i')
    mapid[3] = 'h';
  else if (mapid[3] == 'j')
    mapid[3] = 'g';
  else if (mapid[3] == 'k')
    mapid[3] = 'f';
  else if (mapid[3] == 'l')
    mapid[3] = 'e';
  else if (mapid[3] == 'm')
    mapid[3] = 'l';
  else if (mapid[3] == 'n')
    mapid[3] = 'k';
  else if (mapid[3] == 'o')
    mapid[3] = 'j';
  else if (mapid[3] == 'p')
    mapid[3] = 'i';

  south = bsearch250k(mapid);
  if (south < 0)
    strcpy(mapid, save); /* restore mapid */

  return (south);
}
