/**
 * DOC: -- mapE.c -- find adjacent map to east
 * Peter Thompson 2020
 *
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch250k(char *);
void northpoleE(char *);
void farnorthE(char *);

/**
 * mapE() - find adjacent map to east
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map east
 *         NULL if no such map exists
 */
int mapE(char mapid[]) {
  int east;
  char save[7];

  strcpy(save, mapid); /* save mapid */

  /* North Pole exception handling */
  if (mapid[0] > '1' || (mapid[0] == '1' && mapid[1] == '2')) {
    northpoleE(mapid);
    east = bsearch250k(mapid);
    if (east < 0)
      strcpy(mapid, save); /* restore mapid */
    return (east);
  }

  /*  Far North exception handling */
  if (mapid[2] > '6') {
    farnorthE(mapid);
    east = bsearch250k(mapid);
    if (east < 0)
      strcpy(mapid, save); /* restore mapid */
    return (east);
  }

  /* convert filename to filename adjacent east for rest of Canada */
  if (mapid[3] == 'a') {
    mapid[3] = 'd';
    if (mapid[1] == '0') {
      mapid[1] = '9';
      mapid[0] = '0';
    } else
      mapid[1]--;
  } else if (mapid[3] == 'b')
    mapid[3] = 'a';
  else if (mapid[3] == 'c')
    mapid[3] = 'b';
  else if (mapid[3] == 'd')
    mapid[3] = 'c';
  else if (mapid[3] == 'e')
    mapid[3] = 'f';
  else if (mapid[3] == 'f')
    mapid[3] = 'g';
  else if (mapid[3] == 'g')
    mapid[3] = 'h';
  else if (mapid[3] == 'h') {
    mapid[3] = 'e';
    if (mapid[1] == '0') {
      mapid[1] = '9';
      mapid[0] = '0';
    } else
      mapid[1]--;
  } else if (mapid[3] == 'i') {
    mapid[3] = 'l';
    if (mapid[1] == '0') {
      mapid[1] = '9';
      mapid[0] = '0';
    } else
      mapid[1]--;
  } else if (mapid[3] == 'j')
    mapid[3] = 'i';
  else if (mapid[3] == 'k')
    mapid[3] = 'j';
  else if (mapid[3] == 'l')
    mapid[3] = 'k';
  else if (mapid[3] == 'm')
    mapid[3] = 'n';
  else if (mapid[3] == 'n')
    mapid[3] = 'o';
  else if (mapid[3] == 'o')
    mapid[3] = 'p';
  else if (mapid[3] == 'p') {
    mapid[3] = 'm';
    if (mapid[1] == '0') {
      mapid[1] = '9';
      mapid[0] = '0';
    } else
      mapid[1]--;
  }

  east = bsearch250k(mapid);
  if (east < 0)
    strcpy(mapid, save); /* restore mapid */

  return (east);
}
