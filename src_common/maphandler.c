/**
 * DOC: -- maphandler.c  -- crux of pointer functions connecting oz3 to maps
 * Peter Thompson   -- 2020 March
 *
 *  mapinit() the big switch statement loading appropriate arrays
 *     of function pointers for selected country/usage.
 *  () a list of predefined oz3 functions (see main2fortestin) & associated
 *      double pointer going to a mapset for execution
 *  navinit.c, getinit.c, setinit.c fetinit.c, have 2d arrays
 *    containing function pointers [mapset][function] to executable functions
 *  nav, get, set, fet fcninit() set pointers to appropriate arrays [0][0]
 *    so that function offsets double-point to executable code
 */

/* 22 oz3 predefined function pointers */
#define GONORTH (**(navfcn + 0 + navzm * zm))()
#define GOSOUTH (**(navfcn + 1 + navzm * zm))()
#define GOEAST (**(navfcn + 2 + navzm * zm))()
#define GOWEST (**(navfcn + 3 + navzm * zm))()
#define GONORTHQC (**(navfcn + 4 + navzm * zm))()
#define GOSOUTHQC (**(navfcn + 5 + navzm * zm))()
#define GOEASTQC (**(navfcn + 6 + navzm * zm))()
#define GOWESTQC (**(navfcn + 7 + navzm * zm))()
#define ZOOMINQC (**(navfcn + 8 + navzm * zm))()
#define ZOOMOUTQC (**(navfcn + 9 + navzm * zm))()
#define ZOOMIN (**(navfcn + 10 + navzm * zm))()
#define ZOOMOUT (**(navfcn + 11 + navzm * zm))()
#define DOWNLOAD (**(navfcn + 12 + navzm * zm))()
#define DISPLAY (**(navfcn + 13 + navzm * zm))()
#define COLLARCALC (**(navfcn + 14 + navzm * zm))()
#define COLLARSHOW (**(navfcn + 15 + navzm * zm))()

#define GETMAP (**(getfcn + 0 + getzm * zm))()
#define GETMAPINFO (**(getfcn + 1 + getzm * zm))()

#define SETMAP (**(setfcn + setzm * zm))
#define LLTOPP (**(setfcn + 1 + setzm * zm))
#define PPTOLL (**(setfcn + 2 + setzm * zm))

#define FETCHMAP (**(fetfcn + fetzm * zm))

/* function prototypes */
int (*(*ct_navfcninit()))(); /* navigation functions */
int ct_navfcncnt();
char *(*(*ct_getfcninit()))(); /* getmap functions */
int ct_getfcncnt();
int (*(*ct_setfcninit()))(double *, double *, int *,
                          int *); /* setmap functions */
int ct_setfcncnt();
int (*(*ct_fetfcninit()))(char *); /* fetchmap function */
int ct_fetfcncnt();
int ct_allinit();
int initSDL2();
void closeSDL2();

/* static variables */
static int (*(*navfcn))(); /* navigate functions */
static int navzm; /* count of rows (unique functions) in function array */
static char *(*(*getfcn))(); /* getmap functions */
static int getzm;
static int (*(*setfcn))(); /* navigate functions */
static int setzm;
static int (*(*fetfcn))(); /* navigate functions */
static int fetzm;
static int zm; /* mapset zoom multiplier for array of functions */

/**
 * mapinit() - obtain double function pointer
 *   to array of /country/usage functions
 *
 *  obtain double pointer to array(s) of function pointers
 *   - navfcn = navigation functions: int function()
 *   - getfcn = getmap function: char* function()
 *   - setfcn = set map and position on map: int
 * function(lat,long,pixelx,pixely)
 * @code:   2 char code for /country/usage/
 * return: initial zoom factor for mapset - normally 0
 */
int mapinit(char *code) {
  int returncode;
  int err;

  if ((err = initSDL2()) == 0) /* FALSE = 0, TRUE = 1 */
    return (-1);

  /* begin the big switch statement */
  if (code[0] == 'c' && code[1] == 't') { /* Canada topographic maps */
    navfcn = ct_navfcninit();
    navzm = ct_navfcncnt();
    getfcn = ct_getfcninit();
    getzm = ct_getfcncnt();
    setfcn = ct_setfcninit();
    setzm = ct_setfcncnt();
    fetfcn = ct_fetfcninit();
    fetzm = ct_fetfcncnt();
    returncode = ct_allinit(); /* non-function init - eg arrays */
  }
  /* end the big switch statement */
  return (returncode); /* -1=error, +1=ok */
}

/****************************/
/* 14 int "nav" functions */
int download() { return (DOWNLOAD); }
int display() { return (DISPLAY); }
int gonorth() { return (GONORTH); }
int gosouth() { return (GOSOUTH); }
int goeast() { return (GOEAST); }
int gowest() { return (GOWEST); }
int gonorthqc() { return (GONORTHQC); }
int gosouthqc() { return (GOSOUTHQC); }
int goeastqc() { return (GOEASTQC); }
int gowestqc() { return (GOWESTQC); }
int zoominqc() { return (ZOOMINQC); }
int zoomoutqc() { return (ZOOMOUTQC); }
int zoomin() {
  zm = ZOOMIN;
  return (zm);
}
int zoomout() {
  zm = ZOOMOUT;
  return (zm);
}
int collarcalc() { return (COLLARCALC); }
int collarshow() { return (COLLARSHOW); }

/* 2 char* "get" functions */
char *getmap() { return (GETMAP); }
char *getmapinfo() { return (GETMAPINFO); }

/* 3 int "set" with 4 parameter functions */
int setmap(double *a, double *b, int *c, int *d) {
  int temp;
  temp = SETMAP(a, b, c, d);
  return (temp);
}
/* latlong to pixelpoint */
int lltopp(double *a, double *b, int *c, int *d) {
  int temp;
  temp = LLTOPP(a, b, c, d);
  return (temp);
}
/* pixelpoint to latlong */
int pptoll(double *a, double *b, int *c, int *d) {
  int temp;
  temp = PPTOLL(a, b, c, d);
  return (temp);
}

/* 1 int "sfet" function with 1 char* parameter  */
int fetchmap(char *mapid) {
  int temp;
  temp = FETCHMAP(mapid);
  return (temp);
}

/* 20 total oz3 predefined functions */

void mapclose(void) { closeSDL2(); }
