# Getting started

if you want use this package, at first, put all genomes file (`*.fna` or `*.fa` or `*.fasta`) in one folder, second make a taxonomy tree for these genomes. taxonomy file should make like below:


## Taxonomy tree

#### 1)`taxonomy_tree.txt`: 
this file show order of nodes in taxonomy tree. The first column should contain the number of each node and the second one, contains the parent number of each node. Number of nodes, start with 1. 

#### 2)`seq_id_to_tax_id.txt`:
The taxonomic tree leaves represent our genomes.With considering that the Jellyfish tool receives genomic files in alphabetical order, it is necessary to determine which nodes are associated with genome files.For this reason, in this file, put id that startin with zero, in first column and put node number in second coulmn.
