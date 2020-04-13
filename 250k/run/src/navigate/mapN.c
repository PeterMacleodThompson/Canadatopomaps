/**
 * DOC: -- mapN.c -- find adjacent map to North
 * Peter Thompson 2020
 *
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch250k(char *);
void northpoleN(char *);
void farnorthN(char *);

/**
 * mapN() - find adjacent map to North
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map north
 *         NULL if no such map exists
 */
int mapN(char mapid[]) {
  int north;
  char save[7];

  strcpy(save, mapid); /* save mapid */

  /* North Pole exception handling */
  if (mapid[0] > '1' || (mapid[0] == '1' && mapid[1] == '2')) {
    northpoleN(mapid);
    north = bsearch250k(mapid);
    if (north < 0)
      strcpy(mapid, save); /* restore mapid */
    return (north);
  }

  /*  Far North exception handling */
  if (mapid[2] > '6') {
    farnorthN(mapid);
    north = bsearch250k(mapid);
    if (north < 0)
      strcpy(mapid, save); /* restore mapid */
    return (north);
  }

  /* convert filename to filename adjacent north rest of Canada */
  if (mapid[3] == 'a')
    mapid[3] = 'h';
  else if (mapid[3] == 'b')
    mapid[3] = 'g';
  else if (mapid[3] == 'c')
    mapid[3] = 'f';
  else if (mapid[3] == 'd')
    mapid[3] = 'e';
  else if (mapid[3] == 'e')
    mapid[3] = 'l';
  else if (mapid[3] == 'f')
    mapid[3] = 'k';
  else if (mapid[3] == 'g')
    mapid[3] = 'j';
  else if (mapid[3] == 'h')
    mapid[3] = 'i';
  else if (mapid[3] == 'i')
    mapid[3] = 'p';
  else if (mapid[3] == 'j')
    mapid[3] = 'o';
  else if (mapid[3] == 'k')
    mapid[3] = 'n';
  else if (mapid[3] == 'l')
    mapid[3] = 'm';
  else if (mapid[3] == 'm') {
    mapid[3] = 'd';
    mapid[2]++;
    if (mapid[2] == '7') {
      mapid[3] = 'b';
    }
  } else if (mapid[3] == 'n') {
    mapid[3] = 'c';
    mapid[2]++;
    if (mapid[2] == '7') {
      mapid[3] = 'b';
    }
  } else if (mapid[3] == 'o') {
    mapid[3] = 'b';
    mapid[2]++;
    if (mapid[2] == '7') {
      mapid[3] = 'a';
    }
  } else if (mapid[3] == 'p') {
    mapid[3] = 'a';
    mapid[2]++;
  }

  north = bsearch250k(mapid);
  if (north < 0)
    strcpy(mapid, save); /* restore mapid */

  return (north);
}
