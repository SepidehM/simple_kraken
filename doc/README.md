# Getting started

if you want use this package, at first, put all genomes file (`*.fna` or `*.fa` or `*.fasta`) in one folder, second make a taxonomy tree for these genomes. taxonomy file should make like below:


## Taxonomy tree

#### 1)`taxonomy_tree.txt`: 
this file show order of nodes in taxonomy tree. The first column should contain the number of each node and the second one, contains the parent number of each node. Number of nodes, start with 1. 

#### 2)`seq_id_to_tax_id.txt`:
The taxonomic tree leaves represent our genomes.With considering that the Jellyfish tool receives genomic files in alphabetical order, it is necessary to determine which nodes are associated with genome files.For this reason, in this file, put id that startin with zero, in first column and put node number in second coulmn.



## Make DB 
After make Taxonomy tree and put your genome file in folder, you can run `simple-kraken-db.sh`. this file get `$folder_address`,`$kmer_size`, `$jf file size`, and use [JellyFish](https://github.com/gmarcais/Jellyfish/tree/master/doc) tool for make DB.

```
$ sudo ./simple-kraken-db.sh
```
##### Example Result:
```
[sudo] password for USERNAME: 
***** start simple-kraken DB ****
enter genome files folder address: YOUR_ADDRESS_FILE
enter kmer size:31
enter jf file size(put M in end):100M
***** put all jellyfish file (.jf)  in this folder: YOUR_ADDRESS_FILE ****
start jellyfish
YOUR_ADDRESS_FILE/GCF_000171355.1_ASM17135v1_genomic.fna
YOUR_ADDRESS_FILE/GCF_000027325.1_ASM2732v1_genomic.fna
.
.
.
YOUR_ADDRESS_FILE/ GCF_000195875.1_ASM19587v1_genomic.fna
**** start count in file with Jelly fish ---> output in output_count_in_file.txt  ***
**** put all file name ---> output in name_file.tmp  ***
```

## Starting Simple-kraken
After doing the previous two steps, we can use this package for scoring to `query.fastq` file and find best match in taxonomy tree.

