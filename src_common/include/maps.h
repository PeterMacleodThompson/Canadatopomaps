/**
 * DOC: -- maps.h -- contains oz3 map structure --
 * Peter Thompson Dec 2019 - revised Mar 26, 2020
 *
 *  - 
 *
 * countryusage is:
 *   - located in ~/data/share/oz3/
 *      where country and usage are uniquely identified
 *   - single mapusage - eg aeronautic, marine, topographic, site, 
 *   - single mapcountry - eg Europe, North America, Central America Canada
 *   - one or more mapsets representing different scales
 *   - suite of sprites for each mapactivity 
     - loadable modules for for each mapset for (eg) 
	adjacentmapNorth(currentmapid)
  	adjacentmapEast(currentmapid)
        adjacentmapSouth(currentmapid)
        adjacentmapWest(currentmapid)
 *    
 * all maps, including single maps, must belong to a mapset
 *
 * mapindex is a list of pointers to all map images that make up 1 mapset.
 *   maps in a mapindex can be stitched together to form 1 huge map
 *
 * mapusage is the type of map ( topographic, marine, golf. townsite )
 * mapcountry is the country or geography to which the map belongs
 *
 * 999.9999 degrees = 1 second of latitude = 90 feet = 20 meters
 */

/**
 * mapset - list of all mapsets within a country/usage
 * @name: map name - should match name on original printed map
 * @urlpublic:  public download link used by wget 
 * @urlpmt: private download link for hikingGPS.  contains
 *   country/usage mapsets file, mapindex files, decollared maps 
 *   maps contributed by public, 
 * @kscale: 50=1:50,000, 250=1:250,000 1000=1:1,000,000
 *   mapsets MUST BE SORTED by kscale!! 
 * @boundry: 99.9999 degrees longitude, latitude of outer corners 
 * mapset is a set of maps that:
 *  - have the same scale, and the same "look and feel"
 *  - all maps in a mapset can (ideally) be stitched together to 
 *       form a single huge map
 *  - single URL location where all maps located (hopefully) 
 *     
 */
typedef struct mapset {
  char name[20];   /* eg C50k or C250k = directory name containing maps*/
  char urlpublic[300];  /* source URL for downloading */
  char urlpmt[300]; /* private URL for country/usage,
                        decollared maps, backup copies */
  int kscale;       /* mapsets MUST BE SORTED by kscale  */
  int collarN;      /* y-pixel marking North collar estimate */
  int collarS;      /* y-pixel marking South collar estimate */
  int collarE;      /* x-pixel marking East collar estimate */
  int collarW;      /* x-pixel marking West collar estimate */
  int noblack;      /* grayscale 0-255 below which is converted to white = 255 */
                    /* converts black letters in collar to white  eg 25 */   
} mapset;


/**
 * mapindex - list of all maps in a mapset sorted and indexed
 * @index: record number.  1,2,3,4,... 
 * @mapid: uid -  as found in public download website
 * @mapfilename: wget mapset.urlpublic + mapfilename
 * @mapimagename: SDL image name.  normally mapid.tif
 * @desc: map name on original printed map - optional
 * @latN:  northmost latitude 999.9999
 * @longE:  eastmost longitude 999.9999 
 * @latS:  southmost latitude 999.9999
 * @longW:  westmost longitude 999.9999
 * @pixelwidth:  width of mapimage in pixels
 * @pixelheight: height of mapimage in pixels
 * @mapnorth: index (record number) of adjacent map (to North)
 * @mapeast:  index = 0 ==> on edge, no adjacent map exists 
 * @mapsouth: index = -1 ==> on edge of invisble wall 
 *              adjacent map exists in but in different mapset...
 *               Go up 1 level to find adjacent map.
 * @mapwest:
 * @collarNEx:   collar corner pixel position 
 * @collarNEy:   all = 0 means no collar on map
 * @collarNWx:   for longlat<=>pixel calc
 * @collarNWy: 
 * @collarSEx: 
 * @collarSEy: 
 * @collarSWx: 
 * @collarSWy: 
 * 
 *  1 second = 90 feet, 1 minute = 1 nautical mile
 * non-square maps like marine maps will have white space as part of map 
 * longlat format = 999.9999 accurate to .32 seconds or 30 feet.
 */
typedef struct mapindex {
  int index;		
  char mapid[30];        
  char desc[20];  	
  char mapfilename[50];
  char mapimagename[50]; 
  double latN;         /* map edges in degrees */
  double longE;	
  double latS;	
  double longW;	
  int pixelwidth;      /* map image edges in pixels */
  int pixelheight;
  int mapnorth;   	/* adjacent map index on north */
  int mapeast;
  int mapsouth;
  int mapwest; 
  int collarNEx;      /* pixel collar corners  */
  int collarNEy;
  int collarNWx;
  int collarNWy;
  int collarSEx;
  int collarSEy;
  int collarSWx;
  int collarSWy;
} mapindex;


