#!/bin/bash

#########################
# The command line help #
#########################
display_help() {
    echo 

#    echo "   -a, --all           run all part of simple-kraken"
    echo "   -r, --reduce        reduce output_count_in_file.txt and convert two file"
    echo "			 ---> input: ADDR_FILE/output_count_in_file.txt"
    echo "                       ---> output:"
    echo "                       ---> 	  1) output_kmers.txt"
    echo "                       ---> 	  2) output_seq_node.txt"
    echo
    echo "   -l, --lca           find lca for each kmer after reduce output_count_in_file.txt"
    echo "  			 ---> input:"
    echo "                       ---> 	  1) ADDR_FILE/txonomy_tree.txt"
    echo "                       ---> 	  2) ADDR_FILE/seq_id_to_tax_id.txt"
    echo "                       ---> 	  3) ADDR_FILE/output_seq_node.txt"

    echo "                       ---> output: output_lca_kmers.txt"
    echo
  

    echo "   -m, --minimize      make minimzer for kmer" 
    echo "			 ---> input:"
    echo "                       ---> 	  1) ADDR_FILE/output_kmers.txt"
    echo "                       ---> 	  2) #mimizer_size"
    echo "           		 ---> output:"
    echo "                       ---> 	  1) output_hash_minimizer_to_hash_kmer.txt"
    echo "                       ---> 	  2) output_hash_kmer_to_kmer.txt"


    echo "   -q, --query         find best match taxID for each reads"	
    echo "			 ---> input:"
    echo "                       ---> 	  #) No need type name file, these files should be"
    echo "				     exist in your computer if you call reduce,lca and minimize befor"
    echo "                       ---> 	  1) #kmer_size"
    echo "                       ---> 	  2) #mimizer_size"
    echo "                       ---> 	  3) ADDR_FILE/query.fastq"
    echo "           		 ---> output:"
    echo "                       ---> 	  1) output_taxID_ReadID.txt"

    echo
    echo " [Simple-Kraken Doc] : (https://github.com/SepidehM/simple_kraken/blob/master/doc/README.md)" 
    exit 1
}

################################
# Check if parameters options  #
# are given on the commandline #
################################


while :
do
    case "$1" in
#      -a | --all)
#		kmer="31"
#		minimize="15" 
#		
#		if [ $# -ne 0 ]; then
#		   kmer="$2"
#		   minimize="$3"   
#          	fi
#	
#		./all.out $kmer $minimize
#	
#          exit 0
#          ;;

	-r | --reduce)	
		./reduce_count_file $2
	
          exit 0
          ;;


	-l | --lca)
		./lca_for_kmers $2 $3 $4
	
          exit 0
          ;;

	-m | --minimize)
		./make_minimizer $2 $3 
	
          exit 0
          ;;

	-q | --query)
		./cal_score_for_reads $2 $3 $4
	
          exit 0
          ;;
      -h | --help)
          display_help  # Call your function
          exit 0
          ;;

      --) # End of all options
          shift
          break
          ;;
      -*)
          echo "Error: Unknown option: $1" >&2
          ## or call function display_help
          exit 1 
          ;;
      *)  # No more options
          break
          ;;
    esac
done




 








