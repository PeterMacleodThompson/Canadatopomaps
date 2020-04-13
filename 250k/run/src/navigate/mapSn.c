/**
 * DOC: -- mapWn.c -- find adjacent map to south in Northern Canada
 * Peter Thompson 2020
 *
 */

#include <stdio.h>
#include <stdlib.h> /* for getenv(), exit() */

/* Function Prototypes */
void farnorthW(char *);
void northpoleW(char *);
static void northpole560(char *);
static void northpole340(char *);
static void northpole120(char *);

/**
 * farnorth() - find adjacent map to south in Canada's North
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map south which may or may not exist
 */
void farnorthS(char mapid[]) {
  if (mapid[3] == 'a') {
    mapid[3] = 'h';
    mapid[2]--;
    if (mapid[2] == '6')
      mapid[3] = 'o';
  } else if (mapid[3] == 'b') {
    mapid[3] = 'g';
    mapid[2]--;
    if (mapid[2] == '6')
      mapid[3] = 'm';
  } else if (mapid[3] == 'c')
    mapid[3] = 'b';
  else if (mapid[3] == 'd')
    mapid[3] = 'a';
  else if (mapid[3] == 'e')
    mapid[3] = 'd';
  else if (mapid[3] == 'f')
    mapid[3] = 'c';
  else if (mapid[3] == 'g')
    mapid[3] = 'f';
  else if (mapid[3] == 'h')
    mapid[3] = 'e';

  return;
}

/**
 * northpole() - find adjacent map to south around Canada's north pole
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map south which may or may not exist
 * select one of the north pole areas: 120, 340, 560 for execution
 */
void northpoleS(char mapid[]) {
  if (mapid[0] == '1')
    northpole120(mapid);
  else if (mapid[0] == '3')
    northpole340(mapid);
  else if (mapid[0] == '5')
    northpole560(mapid);
  return;
}

/**
 * northpole560() - find adjacent map to south around Canada's north pole 560
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map south which may or may not exist
 */
static void northpole560(char mapid[]) {
  if (mapid[3] == 'a') {
    mapid[3] = 'g';
    mapid[0] = '0';
    mapid[1] = '5';
    mapid[2] = '9';
  } else if (mapid[3] == 'b') {
    mapid[3] = 'g';
    mapid[0] = '0';
    mapid[1] = '6';
    mapid[2] = '9';
  } else if (mapid[3] == 'd')
    mapid[3] = 'a';

  return;
}

/**
 * northpole340() - find adjacent map to south around Canada's north pole 340
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map south which may or may not exist
 */
static void northpole340(char mapid[]) {
  if (mapid[3] == 'a') {
    mapid[3] = 'g';
    mapid[0] = '0';
    mapid[1] = '3';
    mapid[2] = '9';
  } else if (mapid[3] == 'b') {
    mapid[3] = 'g';
    mapid[0] = '0';
    mapid[1] = '4';
    mapid[2] = '9';
  } else if (mapid[3] == 'c')
    mapid[3] = 'b';
  else if (mapid[3] == 'd')
    mapid[3] = 'a';
  else if (mapid[3] == 'e')
    mapid[3] = 'd';
  else if (mapid[3] == 'f')
    mapid[3] = 'c';

  return;
}

/**
 * northpole120() - find adjacent map to south around Canada's north pole 120
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map south which may or may not exist
 */
static void northpole120(char mapid[]) {
  if (mapid[3] == 'b')
    mapid[3] = 'g'; /* non-existent */
  else if (mapid[3] == 'c')
    mapid[3] = 'b';
  else if (mapid[3] == 'e')
    mapid[3] = 'd'; /* non-existent */
  else if (mapid[3] == 'f')
    mapid[3] = 'c';

  return;
}
