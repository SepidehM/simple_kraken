#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<iterator>
#include<inttypes.h>
#include<map>
#include<limits.h>
#include<vector>
#include<bits/stdc++.h> 
#include<set>
#include<boost/algorithm/string.hpp>
#include<cstdlib>

using namespace std;


bool isParam(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

//==============================

std::map<int,int> read_file_with_2_element(const char* file_name){

	std::map<int,int> data;

	FILE* fp = fopen(file_name, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

	cout<<"start read file!"<<file_name<<endl;
        while ((getline(&line, &len, fp)) != -1) {

                vector<string> strs;
                boost::split(strs,line,boost::is_any_of(" "));
		
		int x1,x2;
		x1 = atoi(strs[0].c_str());
		x2 = atoi(strs[1].c_str());
		data[x1]=x2;

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);

	
	return data;

}

//===============================

vector<int> get_all_parents_for_one_node(int x, map<int,int> &parent_map){
	vector <int>parent;
	int p=x;
	parent.push_back(p);
	while(p!=1){
		parent.push_back(parent_map[p]);	
		p = parent_map[p];
	}

	return parent;			
}

//===============================
int LCA(int x1,int x2,map<int,int> &parent_map){


	vector<int> parent_x1 = get_all_parents_for_one_node(x1, parent_map);
	vector<int> parent_x2 = get_all_parents_for_one_node(x2, parent_map);

	int i = parent_x1.size()-1 , j = parent_x2.size()-1 ;

	int lca = 1;
	while (i>=0 && j>=0){

		if(parent_x1[i] != parent_x2[j])
			break;
		
		lca = parent_x1[i];

		i--;
		j--;

	}
	

	return lca;

}

//==============================
std::map<uint32_t,vector<uint32_t>> read_file_unit32_vector_map(const char* file_name){

        std::map<uint32_t,vector<uint32_t>> data;

        FILE* fp = fopen(file_name, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

        cout<<"start read file "<<file_name<<endl;
        while ((getline(&line, &len, fp)) != -1) {
		string temp = string(line);
		temp = temp.substr(0, temp.length()-1);
                vector<string> strs;
                boost::split(strs,temp,boost::is_any_of(" "));

		//std::set<uint32_t> temp_set;
		//cout<<"d: "<<strs[0]<<" ,s: "<<strs[0].length()<<endl;
                uint32_t x1 = (uint32_t)atol(strs[0].c_str());

			
		for (int i = 1; i< strs.size(); i++){
			//cout<<"d1: "<<strs[i]<<" ,s1: "<<strs[i].length()<<endl;
 			if(isParam(strs[i]) == false)
                                continue;
                        uint32_t temp1 = (uint32_t)atol(strs[i].c_str());
		//	if( temp_set.find(temp1) != temp_set.end()){
		//		temp_set.insert(temp1);
				data[x1].push_back(temp1);			
			//}

		}// end for

		//cout<<"mult:"<<strs.size()-1<<"- size : "<<data[x1].size()<<endl;
				

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);

        return data;

}
//==============================

vector<string> read_file_string_vector(const char* file_name){

        vector<string> data;

        FILE* fp = fopen(file_name, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

        cout<<"start read file "<<file_name<<endl;
        while ((getline(&line, &len, fp)) != -1) {

		string temp = std::string(line);
		data.push_back(temp.substr(0,temp.length()-1));

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);

        return data;

}
//==============================
vector<int> read_file_int_vector(const char* file_name){

        vector<int> data;

        FILE* fp = fopen(file_name, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

        cout<<"start read file "<<file_name<<endl;
        while ((getline(&line, &len, fp)) != -1) {

                vector<string> strs;
                boost::split(strs,line,boost::is_any_of(" "));
		
		//cout<<"num:"<<strs[0]<<endl;
                int x = stoi(strs[0].substr(0,strs[0].length()-1));
		//cout<<"num:"<<x<<endl;
		data.push_back(x);

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);

        return data;

}


//==============================

uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;
  uint32_t h = 0;
  uint32_t k = 0;
  uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
  const uint32_t *chunks = NULL;
  const uint8_t *tail = NULL; // tail - last 8 bytes
  int i = 0;
  int l = len / 4; // chunk length

  h = seed;

  chunks = (const uint32_t *) (d + l * 4); // body
  tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

  // for each 4 byte chunk of `key'
  for (i = -l; i != 0; ++i) {
    // next 4 byte chunk of `key'
    k = chunks[i];

    // encode next 4 byte chunk of `key'
    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    // append to hash
    h ^= k;
    h = (h << r2) | (h >> (32 - r2));
    h = h * m + n;
  }

  k = 0;

  // remainder
  switch (len & 3) { // `len % 4'
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
      k ^= tail[0];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;
      h ^= k;
  }

  h ^= len;

  h ^= (h >> 16);
  h *= 0x85ebca6b;
  h ^= (h >> 13);
  h *= 0xc2b2ae35;
  h ^= (h >> 16);

  return h;
}

//===========================
string make_rev_com_kmer(const char* kmer){

	string rev_com_k = "";
	
	for (int i=strlen(kmer)-1; i>=0; i-- ){
	
		if(kmer[i]=='A'){
			rev_com_k = rev_com_k + 'T';
		}else if(kmer[i]=='T'){
			rev_com_k = rev_com_k + 'A';
		}else if(kmer[i]=='C'){
                        rev_com_k = rev_com_k + 'G';
		}else{
			rev_com_k = rev_com_k + 'C';
		}
	}

	return rev_com_k;
}
//=============================

uint32_t hash_and_xor(const char* str,int len, int seed){
	
	int fix_num = 24573;
	
	uint32_t hash_str = murmurhash(str, (uint32_t)len ,(uint32_t)seed);
	
	hash_str ^= fix_num; 

	return hash_str;
}


//=============================

std::map<int, vector<int>> make_taxonomy_child(map<int,int> &parent_map){
	std::map<int, vector<int>> taxonomy_child;
	
	for (std::pair<int,int> element : parent_map)
                taxonomy_child[element.second].push_back(element.first);


	return taxonomy_child;			
}

//=============================

int main(int argc, char **argv){

	int kmer_size = atoi(argv[1]);
	int minimize_len = atoi(argv[2]);
	unsigned int seed = 23;

	std::map<int,int> data_taxonomy_parent = read_file_with_2_element("txonomy_tree.txt");
	
	std::map<int,vector<int>> data_taxonomy_child = make_taxonomy_child(data_taxonomy_parent);
		

	std::map<uint32_t,vector<uint32_t>> data_minimizerHash_kmerHash = read_file_unit32_vector_map("output_hash_minimizer_to_hash_kmer.txt");
	
	std::map<uint32_t,vector<uint32_t>> data_kmerHash_kmerID= read_file_unit32_vector_map("output_hash_kmer_to_kmer.txt");

	vector<string> data_kmerID_kmer = read_file_string_vector("output_kmers.txt");

	vector<int> data_kmerID_lca = read_file_int_vector("output_lca_kmers.txt");


	FILE* fp = fopen(argv[3], "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;


	std::map<int,string> nodes_reads;
        cout<<"start read fastq file !"<<endl;
	int counter_line = 0;
	int seq_line = 0;

	
	
	while ((getline(&line, &len, fp)) != -1) {
		counter_line = (counter_line+1)%4;		
		if(counter_line!=2)
			continue;	

		string seq = std::string(line);
		vector<int> score;
		for(int j = 0 ; j < data_taxonomy_parent.size()+1; j++)
			score.push_back(0);

		for(int j = 0; j<seq.size()-kmer_size;j++){
			string kmer = std::string(seq.substr(j, kmer_size));
			string rev_kmer = make_rev_com_kmer(kmer.c_str());
			string minimizer="ZZZZZZZZZZZZZZZ";
			uint32_t hash_minimizer = UINT_MAX;
			
			uint32_t h_temp,h_temp_rc;

			string temp="A"+kmer.substr(0,minimize_len-1);
		       	string temp_rc="A"+rev_kmer.substr(0,minimize_len-1);

		        for (int i = minimize_len-1; i< kmer.length()-minimize_len; i++){
		        	temp = temp.substr(1)+kmer[i];
				temp_rc = temp_rc.substr(1)+rev_kmer[i];
				
				h_temp = hash_and_xor(temp.c_str(), minimize_len , seed);
				h_temp_rc = hash_and_xor(temp_rc.c_str(),minimize_len, seed);

				if (h_temp<hash_minimizer){
					minimizer = temp;
					hash_minimizer = h_temp;
				}

				if (h_temp_rc<hash_minimizer){

		                        minimizer = temp_rc;
		                        hash_minimizer = h_temp_rc;
		                }

			}// end for find minimizer

				uint32_t hash_kmer = hash_and_xor(kmer.c_str(), kmer.size(), seed);
			//cout<<"mini:"<<minimizer<<" - hash mini:"<<hash_minimizer<<"- kemer:"<<kmer<<"- hash kmer:"<<hash_kmer<<endl;

			if(data_minimizerHash_kmerHash.find(hash_minimizer) != data_minimizerHash_kmerHash.end()){
					//cout<<"use minimizer:"<<hash_minimizer<<endl;
//				uint32_t hash_kmer = hash_and_xor(kmer.c_str(), kmer.size(), seed);
					//cout<<"hash mini size:"<<data_minimizerHash_kmerHash[hash_minimizer].size()<<endl;
				for(int m = 0 ;m<data_minimizerHash_kmerHash[hash_minimizer].size();m++){
					//cout<<" use !!!!!!!!!!!!!!! "<<data_minimizerHash_kmerHash[hash_minimizer][m]<<endl;
					if (data_minimizerHash_kmerHash[hash_minimizer][m] == hash_kmer) 				
						{	
							//cout<<"size of hash kmer: "<<data_kmerHash_kmerID[hash_kmer].size()<<endl;
							int see = false;
							for(int l= 0 ; l<data_kmerHash_kmerID[hash_kmer].size();l++)
								{
									//cout<<" l: "<<l<<" - data ID: "<<data_kmerHash_kmerID[hash_kmer][l]<<endl;
									//cout<<"data: "<<data_kmerID_kmer[data_kmerHash_kmerID[hash_kmer][l]]<<endl;
									if(kmer == data_kmerID_kmer[data_kmerHash_kmerID[hash_kmer][l]]){
										//cout<<"find :"<<data_kmerHash_kmerID[hash_kmer][l]<<endl;
										score[data_kmerID_lca[data_kmerHash_kmerID[hash_kmer][l]]] +=1;
										see = true;
										break;
									}	
																		
								}
							
						if(see){
						break;
						}
					}
				


				}//end for  exist hash kemer in map
			}// end if exist hash minimizer in map
		

		}//end kmer-size

		// ***** find maximum score ******
		for(int k = 0 ; k<score.size(); k++){
			if (score[k]==0)
				continue;
			for(int m=0; m<	data_taxonomy_child[k].size(); m++)
				score[data_taxonomy_child[k][m]] += score[k];				
				
		}
	
		/*cout<<"\n===============\nseq"<<seq_line<<endl;
		for(int k = 0 ; k<score.size(); k++){					
				cout<<score[k]<<endl;
		}*/		


		int max_node = *max_element(score.begin(), score.end());
		vector<int> max_nodes;
		for(int k = 1 ; k<score.size(); k++)
			if (score[k]==max_node)
				max_nodes.push_back(k);
		
		int lca = max_nodes[0];	

		//cout<<"\n===============\nmax_node"<<lca<<endl;
	
		for(int k = 1; k<max_nodes.size(); k++){
			lca = LCA(lca, max_nodes[k],data_taxonomy_parent);			
			if(lca == 1)
				break;

		}
		
		if(nodes_reads.find(lca) != nodes_reads.end())
			nodes_reads[lca] += to_string(seq_line)+" ";
		else{ 
			nodes_reads[lca] = to_string(seq_line)+" "; 
		}
		
		
		seq_line++;
		

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);

	
	string output ="";
        for (std::pair<int, string> element : nodes_reads) {
                output += "taxID: "+to_string(element.first) +" ";
                output += "readID: "+element.second + "\n";

        }

        cout<<"write TaxID , Read ID"<<endl;
        std::ofstream out1 ("output_taxID_ReadID.txt",std::ofstream::out);
        out1 << output;
        out1.close();


	return 0 ;

}
