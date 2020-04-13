/**
 * DOC: -- mapWn.c -- find adjacent map to West in Northern Canada
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
 * farnorth() - find adjacent map to West in Canada's North
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map west which may or may not exist
 */
void farnorthW(char mapid[]) {
  if (mapid[3] == 'a')
    mapid[3] = 'b';
  else if (mapid[3] == 'b') {
    mapid[3] = 'a';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'c') {
    mapid[3] = 'd';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'd')
    mapid[3] = 'c';
  else if (mapid[3] == 'e')
    mapid[3] = 'f';
  else if (mapid[3] == 'f') {
    mapid[3] = 'e';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'g') {
    mapid[3] = 'h';
    if (mapid[1] == '9') {
      mapid[1] = '0';
      mapid[0] = '1';
    } else
      mapid[1]++;
  } else if (mapid[3] == 'h')
    mapid[3] = 'g';

  return;
}

/**
 * northpole() - find adjacent map to West around Canada's north pole
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map west which may or may not exist
 * select one of the north pole areas: 120, 340, 560 for execution
 */
void northpoleW(char mapid[]) {
  if (mapid[0] == '1')
    northpole120(mapid);
  else if (mapid[0] == '3')
    northpole340(mapid);
  else if (mapid[0] == '5')
    northpole560(mapid);
  return;
}

/**
 * northpole560() - find adjacent map to West around Canada's north pole 560
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map west which may or may not exist
 */
static void northpole560(char mapid[]) {
  if (mapid[3] == 'a')
    mapid[3] = 'b';
  else if (mapid[3] == 'b') {
    mapid[3] = 'a';
    mapid[1]++;
  } else if (mapid[3] == 'c') {
    mapid[3] = 'd';
    mapid[1]++;
  } else if (mapid[3] == 'd')
    mapid[3] = 'c';
  else if (mapid[3] == 'e')
    mapid[3] = 'f';
  else if (mapid[3] == 'f') {
    mapid[3] = 'e';
    mapid[1]++;
  } else if (mapid[3] == 'g') {
    mapid[3] = 'h';
    mapid[1]++;
  } else if (mapid[3] == 'h')
    mapid[3] = 'g';

  return;
}

/**
 * northpole340() - find adjacent map to West around Canada's north pole 340
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map west which may or may not exist
 */
static void northpole340(char mapid[]) {
  if (mapid[3] == 'a')
    mapid[3] = 'b';
  else if (mapid[3] == 'b') {
    mapid[3] = 'a';
    mapid[0] = '5';
    mapid[1] = '6';
  } else if (mapid[3] == 'c') {
    mapid[3] = 'd';
    mapid[0] = '5';
    mapid[1] = '6';
  } else if (mapid[3] == 'd')
    mapid[3] = 'c';
  else if (mapid[3] == 'e')
    mapid[3] = 'f';
  else if (mapid[3] == 'f') {
    mapid[3] = 'e';
    mapid[0] = '5';
    mapid[1] = '6';
  } else if (mapid[3] == 'g') {
    mapid[3] = 'h';
    mapid[0] = '5';
    mapid[1] = '6';
  } else if (mapid[3] == 'h')
    mapid[3] = 'g';

  return;
}

/**
 * northpole120() - find adjacent map to West around Canada's north pole 120
 * area
 * @mapid: pointer to 4 char map identifier showing to current map in maplist
 *     map identifier changed to 1 map west which may or may not exist
 */
static void northpole120(char mapid[]) {
  if (mapid[3] == 'a')
    mapid[3] = 'b';
  else if (mapid[3] == 'b') {
    mapid[3] = 'a';
    mapid[0] = '3';
    mapid[1] = '4';
  } else if (mapid[3] == 'c') {
    mapid[3] = 'd';
    mapid[0] = '3';
    mapid[1] = '4';
  } else if (mapid[3] == 'd')
    mapid[3] = 'c';
  else if (mapid[3] == 'e')
    mapid[3] = 'f';
  else if (mapid[3] == 'f') {
    mapid[3] = 'e';
    mapid[0] = '3';
    mapid[1] = '4';
  } else if (mapid[3] == 'g') {
    mapid[3] = 'h';
    mapid[0] = '3';
    mapid[1] = '4';
  } else if (mapid[3] == 'h')
    mapid[3] = 'g';

  return;
}
