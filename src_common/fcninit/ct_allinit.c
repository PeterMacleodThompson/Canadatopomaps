/* ct_allinit.c  - general initialization (non function pointer)
 * forCanada/topographic Peter Thompson March 2020
 *
 * initializes map arrays used for binary search
 *
 * TODO move this program to /Canada/topographic/maps/src/ - here for testing
 * only
 */
#include "maps.h"
#include <stdlib.h>

/* function prototypes */
int init250k(void);
int init50k(void);
int init1m(void);
mapset *initmapset(mapset *, char *);
char *getmappath(void);

int ct_allinit(void) {
  int err;

  initmapset(NULL, getmappath());
  if ((err = init250k()) < 0)
    return (-1);
  else if ((err = init50k()) < 0)
    return (-1);
  else if ((err = init1m()) < 0)
    return (-1);
  else
    return (1);
}
