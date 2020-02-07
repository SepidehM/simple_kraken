//typedef unsigned __int64 uint64_t;

#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<iterator>
#include<inttypes.h>
#include<map>
#include<limits.h>

using namespace std;

//================================
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
string make_rev_com_kemr(const char* kmer){

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
int main(int argc, char **argv){


	FILE* fp = fopen(argv[1], "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

        cout<<"start make minimizer from kmer and reverse_com !"<<endl;

	int minimize_len = atoi(argv[2]);
	unsigned int seed = 23;

	map<uint32_t,string> hash_minimizer_hash_kmer;
	map<uint32_t,string> hash_kmer_to_kmer;

	int line_number = 0;

        while ((getline(&line, &len, fp)) != -1) {


		string kmer = std::string(line);
		kmer = kmer.substr(0,kmer.length()-1);

		string rev_kmer = make_rev_com_kemr(kmer.c_str());
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
		
		//cout<<"mini : " <<minimizer<<endl;
		//cout<<"mini -hash : " <<hash_minimizer<<endl;
		//cout<<"kmers : " <<kmer<<endl;
		uint32_t hash_kmer = hash_and_xor(kmer.c_str(), kmer.size(), seed);
		//cout<<"hash_kmers:"<<hash_kmer<<endl;
	       
		if (hash_minimizer_hash_kmer.find(hash_minimizer) != hash_minimizer_hash_kmer.end()) 
			hash_minimizer_hash_kmer[hash_minimizer] += " "+to_string(hash_kmer);
		else
			hash_minimizer_hash_kmer[hash_minimizer] = to_string(hash_kmer);

		if(hash_kmer_to_kmer.find(hash_kmer) != hash_kmer_to_kmer.end())
			hash_kmer_to_kmer[hash_kmer] += " "+to_string(line_number);

		else
			hash_kmer_to_kmer[hash_kmer] = to_string(line_number);

		line_number++;
        }// end file read lines
        fclose(fp);
        if (line)
                free(line);


	string output_hash_minimizer_to_hash_kmer ="";
        string output_hash_kmer_to_kmer ="";
	

	// Iterate over the map using c++11 range based for loop
	for (std::pair<uint32_t, string> element : hash_minimizer_hash_kmer) {
		output_hash_minimizer_to_hash_kmer += to_string(element.first) +" ";
		output_hash_minimizer_to_hash_kmer += element.second + "\n";

	}

	// Iterate over the map using c++11 range based for loop
        for (std::pair<uint32_t, string> element : hash_kmer_to_kmer) {
                output_hash_kmer_to_kmer += to_string(element.first) +" ";
                output_hash_kmer_to_kmer += element.second + "\n";

        }

        cout<<"write hash minimizer , hash kmer"<<endl;
        std::ofstream out1 ("output_hash_minimizer_to_hash_kmer.txt",std::ofstream::out);
        out1 << output_hash_minimizer_to_hash_kmer;
        out1.close();


	cout<<"write hash of kmers , kmers"<<endl;

        std::ofstream out2 ("output_hash_kmer_to_kmer.txt",std::ofstream::out);
        out2 << output_hash_kmer_to_kmer;
        out2.close();



	return 0;
}
