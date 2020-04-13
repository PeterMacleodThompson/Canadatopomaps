#!/bin/sh

#  DOWNLOAD topo maps 1:1,000,000 from website
#  http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/1m_tif/
#
#  EXAMPLE http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/1m_tif/10/
#   yields 3 maps: 
#      - canmatrix2_nn_10_1_tif.zip == Prince George Edition 1
#      - canmatrix2_nn_10_2_tif.zip == Prince George Edition 1   USE THIS -smaller
#      - canmatrix2_nn_10_tif.zip  == Fort Nelson Edition 1 copyright 1977
# 
#         _1_ and _2_ seem identical ?????? arbitrarily selected one of them
#  ----------------------------------------------------------------


echo "spider is looking for files in... "
echo "   ...http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/1m_tif/ "
wget --spider --recursive --no-parent --no-directories --no-host-directories     \
        --output-file=work1 --progress=bar:force:noscroll                        \
        ftp://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/1m_tif/ 

wc -l work1
echo "spider done - starting 3 greps to get list of files"
grep //ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/1m_tif/  work1 > work2
grep canmatrix work2 > work3
grep done.    work3 > work4
wc -l work4    # 100 records - 31 are duplicates

cut -c 115- work4 > work5
 
# make duplicat maps duplicate
sed -i "s/_2_/_1_/" work5
sed -i "s/_3_/_1_/" work5

echo "sort, then remove duplicates "
sort work5 > work6
uniq work6 > work7
echo "DONE"
wc -l work7
echo " you should have 69 unique map files in Canada/topographic/maps/3raw/1m/maplist."
cp work7 ../../3raw/1m/maplist
#  rm work*




# TROUBLESHOOTING
# 1. chmod 755 spider1m.sh -- run this to 
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
