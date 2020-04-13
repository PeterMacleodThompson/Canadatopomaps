/* ct_setinit.c  - links Canada/topographic functions with arguments to
 * hikingGPS oz3 Peter Thompson March 2020
 *
 * defines the array of int functions which have 4 arguments
 * 2 long, 2 int  for Canada/topographic maps
 *
 * TODO move this program to /Canada/topographic/maps/src/ - here for testing
 * only
 */

#include <stdio.h>

/* setmap function prototypes */
int ct1m_setmap(double *, double *, int *, int *);
int ct1m_lltopp(double *, double *, int *, int *);
int ct1m_pptoll(double *, double *, int *, int *);
int ct2k_setmap(double *, double *, int *, int *);
int ct2k_lltopp(double *, double *, int *, int *);
int ct2k_pptoll(double *, double *, int *, int *);
int ct5k_setmap(double *, double *, int *, int *);
int ct5k_lltopp(double *, double *, int *, int *);
int ct5k_pptoll(double *, double *, int *, int *);

/* setmap array[3]mapsets x [3]mapfunctions  of function pointers */
static int (*fsetptr[3][3])() = {
    {&ct1m_setmap, &ct1m_lltopp, &ct1m_pptoll},
    {&ct2k_setmap, &ct2k_lltopp, &ct2k_pptoll},
    {&ct5k_setmap, &ct5k_lltopp, &ct5k_pptoll},
};

/* setmap functions init */
int (*(*ct_setfcninit()))() { return (&fsetptr[0][0]); }

/* setmap function count*/
int ct_setfcncnt() { return (3); }
