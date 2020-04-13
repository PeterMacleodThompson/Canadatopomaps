#!/bin/sh

#  DOWNLOAD topo maps 1:250,000 from website
#  http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/
#
#  EXAMPLE http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/031/e/
#   yields 5 maps: 
#	031e_0200_canmatrix_prtpdf.zip	104M	 
#	031e_0200_canmatrix_prttif.zip	123M	OLD Version, don;t use 
#       031e_0300_canmatrix_geotif.zip   14M
#       031e_0300_canmatrix_prtpdf.zip   15M
#       031e_0300_canmatrix_prttif.zip   13M	 USE THIS ONE
#     
#        0200 is 2nd edition, 0300 is 3rd edition.  Use 3rd edition 
#  ----------------------------------------------------------------


echo "spider is looking for files in... "
echo "   ...http://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/ "
wget --spider --recursive --no-parent --no-directories --no-host-directories     \
        --output-file=work1                                                     \
        ftp://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/ 


echo "spider done, find lines = File 'filename' exists "
grep exists work1 > work2      # remove garbage lines
grep canmatrix work2 > work3   # select only canmatrix files 
grep prttif.zip work3 > work4  # select only prttif files
wc -l work4   # 1776 records


#use sed to isolate filename
echo "sed out garbage characters & isolate filename (4 passes)"
# remove UTF-8 left single quotation mark   -i does in-place edit  
sed  -i  "s/\xe2\x80\x98//g" work4 
# remove UTF-8 right single quotation mark
sed  -i  "s/\xe2\x80\x99//g" work4
# remove "File " 
sed -i "s/File //" work4  
# remove " exists."
sed -i "s/ exists.//" work4  


# sort in reverse order so newest (latest edition) map selected
echo "sort, then remove duplicates   mapid is 1st 4 chars"
sort --reverse        work4 > work5
uniq --check-chars=4  work5 > work6

# restore normal sort order
sort work6 > work7

echo "DONE"
wc -l work7
echo " you should have 913 unique map files in Canada/topographic/maps/3raw/250k/maplist."
cp work7 ../../3raw/250k/maplist
#  rm work*



#separate 1st edition _0100  2nd edition _0200_  3rd edition _0300_
#grep _0100_ work4 > work0100   # 363 records  4th
#grep _0101_ work4 > work0100   #   1 records
#grep _0102_ work4 > work0100   #   1 records
#grep _0200_ work4 > work0200   # 672 records  2nd choice
#grep _0201_ work4 > work0100   #   2 records
#grep _0202_ work4 > work0100   #   1 records
#grep _0300_ work4 > work0300   # 521 records  1st choice
#grep _0400_ work4 > work0400   # 153 records  3rd 
#grep _0500_ work4 > work0500   #  38 records  5th
#grep _0600_ work4 > work0600   #  15 records  6th
#grep _0700_ work4 > work0700   #   7 records
#grep _0800_ work4 > work0800   #   2 records
# total 1776 



# TROUBLESHOOTING
# 1. chmod 755 spider250k.sh -- run this to 
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
