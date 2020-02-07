# Getting started

if you want use this package, at first, put all genomes file (`*.fna` or `*.fa` or `*.fasta`) in one folder, second make a taxonomy tree for these genomes. taxonomy file should make like below:


## Taxonomy tree

#### 1)`taxonomy_tree.txt`: 
this file show order of nodes in taxonomy tree. The first column should contain the number of each node and the second one, contains the parent number of each node. Number of nodes, start with 1. 

#### 2)`seq_id_to_tax_id.txt`:
The taxonomic tree leaves represent our genomes.With considering that the Jellyfish tool receives genomic files in alphabetical order, it is necessary to determine which nodes are associated with genome files.For this reason, in this file, put id that startin with zero, in first column and put node number in second coulmn.

###### Example of Taxonomy tree (extract from [itol.embl.de](https://itol.embl.de/itol.cgi) site):
![TaX tree](https://github.com/SepidehM/simple_kraken/blob/master/doc/taxonomy-tree.png)

###### Exapmle of `taxonomy_tree.txt`:
```
2 1
3 2
4 2
5 4
6 4
7 1
8 7
9 7
10 9
11 9
12 11
13 11
14 13
15 13
16 15
17 15
18 17
19 17
```

###### Exapmle of `Order of bacteria fasta file in genome folder`:
```
 ['GCF_000762305.1', 'Clostridium tetani'],
 ['GCF_000009685.1', 'Clostridium perfringens str. 13'],
 ['GCF_002006385.1', 'Clostridium acetobutylicum'],
 ['GCF_000011445.1', 'Mycoplasma mycoides subsp. mycoides SC str. PG1'],
 ['GCF_000195875.1', 'Mycoplasma pulmonis UAB CTIP'],
 ['GCF_000171355.1', 'Ureaplasma parvum serovar 14 str. ATCC 33697'],
 ['GCF_000011225.1', 'Mycoplasma penetrans HF-2'],
 ['GCF_000286675.1', 'Mycoplasma gallisepticum VA94_7994-1-7P'],
 ['GCF_000319675.2', 'Mycoplasma pneumoniae PI 1428'],
 ['GCF_000027325.1', 'Mycoplasma genitalium G37'],
 
```

###### Exapmle of `seq_id_to_tax_id.txt`:
```
0 6
1 14
2 8
3 19
4 12
5 10
6 16
7 18
8 5
9 3
```

#### Notice: if you want see all kind of bacteria in assembly file and extract some of them, use my python code in [folder python]().




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

#### Notice: 
if you want make fastq file from genome, use my python code in [folder python]().



#### Start simple-kraken with help: 

```
$ ./simple-kraken.sh -h

   -r, --reduce        reduce output_count_in_file.txt and convert two file
			 ---> input: ADDR_FILE/output_count_in_file.txt
                       ---> output:
                       ---> 	  1) output_kmers.txt
                       ---> 	  2) output_seq_node.txt

   -l, --lca           find lca for each kmer after reduce output_count_in_file.txt
  			 ---> input:
                       ---> 	  1) ADDR_FILE/txonomy_tree.txt
                       ---> 	  2) ADDR_FILE/seq_id_to_tax_id.txt
                       ---> 	  3) ADDR_FILE/output_seq_node.txt
                       ---> output: output_lca_kmers.txt

   -m, --minimize      make minimzer for kmer
			 ---> input:
                       ---> 	  1) ADDR_FILE/output_kmers.txt
                       ---> 	  2) #mimizer_size
           		 ---> output:
                       ---> 	  1) output_hash_minimizer_to_hash_kmer.txt
                       ---> 	  2) output_hash_kmer_to_kmer.txt
   -q, --query         find best match taxID for each reads
			 ---> input:
                       ---> 	  #) No need type name file, these files should be
				     exist in your computer if you call reduce,lca and minimize befor
                       ---> 	  1) #kmer_size
                       ---> 	  2) #mimizer_size
                       ---> 	  3) ADDR_FILE/query.fastq
           		 ---> output:
                       ---> 	  1) output_taxID_ReadID.txt

 [Simple-Kraken Doc] : (https://github.com/SepidehM/simple_kraken/blob/master/doc/README.md)

```



### Steps :

### 1) Make File: 
use make file in folder simple-kraken

```
$ make
```

result:

```
g++     reduce_count_file.cpp   -o reduce_count_file
g++     lca_for_kmers.cpp   -o lca_for_kmers
g++     cal_score_for_reads.cpp   -o cal_score_for_reads
g++     make_minimizer.cpp   -o make_minimizer
```

### 2) Reduce:
at first, we want reduce size of `output_count_in_file.txt`. this file divide 2 parts.
```
./simple-kraken.sh -r  ADDR_FILE/output_count_in_file.txt
```
result:
```
your file name:ADDR_FILE/output_count_in_file.txt
start !
write in file kemrs
write in file seq node
```

#### Outputs(Examples):
##### 2.1)output_kmers.txt:
this file contain all kmers. 

##### 2.2)output_seq_node.txt:
this file contain genome numbers that have kmer.



### 3) LCA:
atfer find all genome numbers for each kmer, we should find least common ancestor for each kmer.
```
./simple-kraken.sh -l ADDR_FILE/txonomy_tree.txt ADDR_FILE/seq_id_to_tax_id.txt ADDR_FILE/output_seq_node.txt
```
result:
```
start !
start !
start lca!

```

#### Outputs(Examples):
##### 3.1)output_lca_kmers.txt
this file contain lca for each kmer.



### 4) Minimize:
after find all lca for each kmer, we should find minimizer for kmers and for reduce size, we use hash function.
```
```

#### Outputs(Examples):
##### 4.1)output_hash_minimizer_to_hash_kmer.txt
this file contain hash of minimizer of each kmer in fisrt column and hash of kmers in second column.

##### 4.1)output_hash_kmer_to_kmer.txt
this file contain hash of kmers in fisrt column and ID of kmers in second column.


### 5) Query:
after minimize kmers, we get query file and find best match for each read.
```
```

#### Outputs(Examples):
##### 5.1)output_taxID_ReadID.txt
this file conation, taxID in first column and ReadID that assigned to it in second column.
