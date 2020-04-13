/* ct_getinit.c  - links Canada/topographic map character functions to hikingGPS
 * oz3 Peter Thompson March 2020
 *
 * defines the array of getmap functions for Canada/topographic maps
 *
 * TODO move this program to /Canada/topographic/maps/src/ - here for testing
 * only
 */

#include <stdio.h>

/* getmap function prototypes
 *   ==> mapnow */
char *ct1m_getmap();
char *ct2k_getmap();
char *ct5k_getmap();
char *ct1m_getmapinfo();
char *ct2k_getmapinfo();
char *ct5k_getmapinfo();

/* getmap array[3]mapsets = 3 function pointers */
static char *(*fgetptr[3][2])() = {{&ct1m_getmap, &ct1m_getmapinfo},
                                   {&ct2k_getmap, &ct2k_getmapinfo},
                                   {&ct5k_getmap, &ct5k_getmapinfo}};

/* getmap function init */
char *(*(*ct_getfcninit()))() { return (&fgetptr[0][0]); }

/* getmap function count*/
int ct_getfcncnt() { return (2); }
