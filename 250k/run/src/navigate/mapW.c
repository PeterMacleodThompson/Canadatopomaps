/**
 * DOC: -- mapW.c -- find adjacent map to West
 * Peter Thompson 2020
 *
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */
#include <string.h>

/* Function Prototypes */
int bsearch250k(char *);
void northpoleW(char *);
void farnorthW(char *);

/**
 * mapW() - find adjacent map to West
 * @index: pointer  to current map in maplist
 * return: pointer to adjacent map west
 *         NULL if no such map exists
 */
int mapW(char mapid[]) {
  int west;
  char save[7];

  strcpy(save, mapid); /* save mapid */

  /* North Pole exception handling */
  if (mapid[0] > '1' || (mapid[0] == '1' && mapid[1] == '2')) {
    northpoleW(mapid);
    west = bsearch250k(mapid);
    if (west < 0)
      strcpy(mapid, save); /* restore mapid */
    return (west);
  }

  /*  Far North exception handling */
  if (mapid[2] > '6') {
    farnorthW(mapid);
    west = bsearch250k(mapid);
    if (west < 0)
      strcpy(mapid, save); /* restore mapid */
    return (west);
  }

  /* convert filename to filename adjacent west for rest of Canada */
  if (mapid[3] == 'a')
    mapid[3] = 'b';
  else if (mapid[3] == 'b')
    mapid[3] = 'c';
  else if (mapid[3] == 'c')
    mapid[3] = 'd';
  else if (mapid[3] == 'd') {
    mapid[3] = 'a';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'e') {
    mapid[3] = 'h';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'f')
    mapid[3] = 'e';
  else if (mapid[3] == 'g')
    mapid[3] = 'f';
  else if (mapid[3] == 'h')
    mapid[3] = 'g';
  else if (mapid[3] == 'i')
    mapid[3] = 'j';
  else if (mapid[3] == 'j')
    mapid[3] = 'k';
  else if (mapid[3] == 'k')
    mapid[3] = 'l';
  else if (mapid[3] == 'l') {
    mapid[3] = 'i';
    mapid[3] = 'h';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'm') {
    mapid[3] = 'p';
    mapid[3] = 'h';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'n')
    mapid[3] = 'm';
  else if (mapid[3] == 'o')
    mapid[3] = 'n';
  else if (mapid[3] == 'p')
    mapid[3] = 'o';

  west = bsearch250k(mapid);
  if (west < 0)
    strcpy(mapid, save); /* restore mapid */

  return (west);
}
