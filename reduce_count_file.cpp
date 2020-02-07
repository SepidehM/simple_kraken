#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>


using namespace std;

int main(int argc, char **argv){

	cout<<"your file name:"<<argv[1]<<endl;
	
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL)
   		exit(EXIT_FAILURE);

	char* line = NULL;
	size_t len = 0;

	string output_kmers = "";
	string output_seq_node = "";

	cout<<"start !"<<endl;
	while ((getline(&line, &len, fp)) != -1) {
    	
		vector<string> strs;
        	boost::split(strs,line,boost::is_any_of(" "));

		output_kmers +=strs[0]+"\n";

		for (int i = 1; i< strs.size(); i++){
			if (i+1 == strs.size()){
				//cout<<"t"<<strs[i];
				strs[i] = strs[i].substr(0,1);
				//cout<<"d"<<strs[i]<<"\n=========="<<endl;
			
			}
			
			if(strs[i]!="0")
				output_seq_node += to_string(i-1)+" ";
		
		}// end for : select number not zero count
		output_seq_node +="\n";

	}// end file read lines
	fclose(fp);
	if (line)
    		free(line);

	cout<<"write in file kemrs"<<endl;

	std::ofstream out1 ("output_kmers.txt",std::ofstream::out);
    	out1 << output_kmers;
    	out1.close();

	cout<<"write in file seq node"<<endl;
    	std::ofstream out2 ("output_seq_node.txt",std::ofstream::out);
    	out2 << output_seq_node;
    	out2.close();


	return 0;

}
