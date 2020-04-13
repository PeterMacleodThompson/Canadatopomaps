/* ct_fetinit.c  - links Canada/topographic int function 1 char* parameter to
 * hikingGPS oz3 Peter Thompson March 2020
 *
 * defines the array of getmap functions for Canada/topographic maps
 *
 * TODO move this program to /Canada/topographic/maps/src/ - here for testing
 * only
 */

#include <stdio.h>

/* getmap function prototypes  fet = fetch */
char *ct1m_fetmap();
char *ct2k_fetmap();
char *ct5k_fetmap();

/* getmap array[3]mapsets = 3 function pointers */
static char *(*ffetptr[3])() = {
    &ct1m_fetmap,
    &ct2k_fetmap,
    &ct5k_fetmap,
};

/* getmap function init */
char *(*(*ct_fetfcninit()))() { return (&ffetptr[0]); }

/* getmap function count*/
int ct_fetfcncnt() { return (1); }
