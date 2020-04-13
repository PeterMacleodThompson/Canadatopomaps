#!/bin/sh

#  DOWNLOAD topo maps 1:50,000 from website
#  http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/50k/
#
#  EXAMPLE http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/50k/031/e/01/
#   yields 7 maps: 
#   031e01_0500_canmatrix_geotiff.zip  => .tif + .xml = embedded geo data =10x size
#   031e01_0500_canmatrix_prtpdf.zip => pdf version 
#   031e01_0500_canmatrix_prttif.zip => USE THIS 
#   031e01_0600_cantopo_geopdf.zip
#   031e01_0600_cantopo_geotiff.zip
#   031e01_0600_cantopo_pdf.zip
#   031e01_0600_cantopo_tif.zip ==> NOT AS GOOD - 2ND CHOICE LOOKS LIKE TOPORAMA
#     
#        0200 is 2nd edition, 0300 is 3rd edition.  Use 3rd edition 
#  ----------------------------------------------------------------


echo "spider is looking for files in... "
echo "   ...http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/50k/ "
date
date
wget --spider --recursive --no-parent --no-directories --no-host-directories     \
        --output-file=work1                                                     \
        ftp://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/50k/ 
date
date
wc -l work1    # work1 = 96,099 records   work2  = 12,012 records
echo "spider done - starting 3 greps to get list of files"
grep //ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/50k/  work1 > work2
grep canmatrix     work2 > work3    #  = 8998 records
grep prttif.zip    work3 > work4    #  = 3552 records
grep done.         work4 > work5    #  = 1776 records

cut -c 47- work5 > work6

# sort in reverse order so newest (latest edition) map selected
echo "sort, then remove duplicates   mapid is 1st 4 chars"
sort --reverse        work5 > work6
uniq --check-chars=4  work6 > work7

# restore normal sort order
sort work7 > work8

echo "DONE"
wc -l work8
echo " you should have 12,119 unique map files in Canada/topographic/maps/3raw/50k/maplist."
cp work8 ../../3raw/50k/maplist
#  rm work*



# TROUBLESHOOTING
# 1. chmod 755 spider50k.sh -- run this to 
#     change permissions before executing this script
# 2. debugging script?  put echo in front of the command
# 3. run this shell using commandline ./spider1m.sh runs the shell
#
#
# --spider => will not download pages, just check they are there. 
# -r => --recursive 
# --output-file=logfile NO I THINK
# --no-directories   YES
# --no-host-directories YES
# --recursive YES
# --level=3  DEFAULT IS 5
# --no-parent  YES never ascend to parent directory for recursive retrieve
#  --accept "*,zip"   NO suffixes to accept but all are .zip
# --input-file=myfile
# --base=url
# --show-progress
# sed -e add the script to the command to be executed NOT USED
