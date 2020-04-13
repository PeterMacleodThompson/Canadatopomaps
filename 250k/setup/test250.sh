#!/bin/sh

test.sh

work1 = 96,099 records
grep //ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/  # work98 12,012 records 

grep canmatrix     work97 = 8998 records
grep prttif.zip    work96 = 3552 records
grep done.         work95 = 1776 records   works!!!

cut -c 47- work95 > work94


 below WORKS AND IS FAST (approx 10 sec)== 8.4MB download, (midnight)
FLORIDA NAPLES download=41.7Mbps Upload=3.79Mbps  ipaddress=69.247.248.152
wget ftp://ftp.maps.canada.ca/pub/nrcan_rncan/raster/topographic/250k/014/e/014e_0100_canmatrix_prttif.zip    





After download, get map name by looking in 
014e_0101_canmatrix2_pna.xml   (or *.xml)
andthen 
grep "CanMatrix - Print Ready -" 014e_0101_canmatrix2_pna.xml > work50

sed remove text between angle brackets 
sed "s/<[^>]*>//g" work50 > work49
sed remove other non-title text  
sed "s/CanMatrix - Print Ready -//"  work49 > work48

echo done 





