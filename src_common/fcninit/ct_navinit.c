/* ct_navinit.c  - links Canada/topographic map navigation functions to
 * hikingGPS oz3 Peter Thompson March 2020
 *
 * defines the array of navigation functions for Canada/topographic maps
 *
 * TODO move this program to /Canada/topographic/maps/src/ - here for testing
 * only
 */

/* navigation function prototypes
 *   ==> int, no args: 16 functions * 3 mapsets = 42 */
int ct1m_gonorth();
int ct1m_gosouth();
int ct1m_goeast();
int ct1m_gowest();
int ct1m_gonorthqc();
int ct1m_gosouthqc();
int ct1m_goeastqc();
int ct1m_gowestqc();
int ct1m_zoominqc();
int ct1m_zoomoutqc();
int ct1m_zoomin();
int ct1m_zoomout();
int ct1m_download();
int ct1m_display();
int ct1m_collarcalc();
int ct1m_collarshow();

int ct2k_gonorth();
int ct2k_gosouth();
int ct2k_goeast();
int ct2k_gowest();
int ct2k_gonorthqc();
int ct2k_gosouthqc();
int ct2k_goeastqc();
int ct2k_gowestqc();
int ct2k_zoominqc();
int ct2k_zoomoutqc();
int ct2k_zoomin();
int ct2k_zoomout();
int ct2k_download();
int ct2k_display();
int ct2k_collarcalc();
int ct2k_collarshow();

int ct5k_gonorth();
int ct5k_gosouth();
int ct5k_goeast();
int ct5k_gowest();
int ct5k_gonorthqc();
int ct5k_gosouthqc();
int ct5k_goeastqc();
int ct5k_gowestqc();
int ct5k_zoominqc();
int ct5k_zoomoutqc();
int ct5k_zoomin();
int ct5k_zoomout();
int ct5k_download();
int ct5k_display();
int ct5k_collarcalc();
int ct5k_collarshow();

/* navigation array[3]mapsets x [16]mapfunctions  of function pointers */
static int (*fptr[3][16])() = {
    {&ct1m_gonorth, &ct1m_gosouth, &ct1m_goeast, &ct1m_gowest, &ct1m_gonorthqc,
     &ct1m_gosouthqc, &ct1m_goeastqc, &ct1m_gowestqc, &ct1m_zoominqc,
     &ct1m_zoomoutqc, &ct1m_zoomin, &ct1m_zoomout, &ct1m_download,
     &ct1m_display, ct1m_collarcalc, ct1m_collarshow},
    {&ct2k_gonorth, &ct2k_gosouth, &ct2k_goeast, &ct2k_gowest, &ct2k_gonorthqc,
     &ct2k_gosouthqc, &ct2k_goeastqc, &ct2k_gowestqc, &ct2k_zoominqc,
     &ct2k_zoomoutqc, &ct2k_zoomin, &ct2k_zoomout, &ct2k_download,
     &ct2k_display, ct2k_collarcalc, ct2k_collarshow},
    {&ct5k_gonorth, &ct5k_gosouth, &ct5k_goeast, &ct5k_gowest, &ct5k_gonorthqc,
     &ct5k_gosouthqc, &ct5k_goeastqc, &ct5k_gowestqc, &ct5k_zoominqc,
     &ct5k_zoomoutqc, &ct5k_zoomin, &ct5k_zoomout, &ct5k_download,
     &ct5k_display, ct5k_collarcalc, ct5k_collarshow},
};

/* navigation functions init */
int (*(*ct_navfcninit()))() { return (&fptr[0][0]); }

/* navigation function count*/
int ct_navfcncnt() { return (16); }
