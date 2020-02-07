#!/bin/bash
echo '***** start simple-kraken DB ****'

read -p 'enter genome files folder address:' address_folder
read -p 'enter kmer size:' kmer_s
read -p 'enter jf file size(put M in end):' jf_s

echo '***** put all jellyfish file (.jf)  in this folder:' $address_folder ' ****'

echo "start jellyfish";

find  $address_folder -name "*.fna" | while read m; do echo $m; jellyfish count -m $kmer_s -s $jf_s -C $m -o $m.jf; done

x=''

for filename in $(ls $address_folder/*.jf)
do

  #y=$(cut -d'/' -f7 <<<"$filename")
  x="${x} ${filename}"

done;

echo "**** start count in file with Jelly fish ---> output in output_count_in_file.txt  ***";

/usr/local/Jellyfish/examples/count_in_file/count_in_file $x > $address_folder/output_count_in_file.txt


echo "**** put all file name ---> output in name_file.tmp  ***";

find $address_folder -maxdepth 1 -name "*.fna" | while read m ; do head -n 1 $m; done | cut -d' ' -f1  > x.tmp;

x=''
for filename in $(ls $address_folder/*.fna)
do
  y=$(cut -d'/' -f7 <<<"$filename")
  z=$(head -n 1 $filename| cut -d' ' -f1)
  x=$x$y" "${z:1}$'\n'
done;

cat <<< $x > name_file.tmp;

 








