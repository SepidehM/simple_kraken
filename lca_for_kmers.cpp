#include<iostream>
#include<string>
#include<fstream>
#include<vector> 
#include<iterator> 
#include<map>
#include <boost/algorithm/string.hpp>


using namespace std;

/*
struct node {
    int data;
    struct node *parent;
    list <node*> childs;
};
*/



std::map<int,int> read_file_with_2_element(const char* file_name){

	std::map<int,int> data;

	FILE* fp = fopen(file_name, "r");
        if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

	cout<<"start !"<<endl;
        while ((getline(&line, &len, fp)) != -1) {

                vector<string> strs;
                boost::split(strs,line,boost::is_any_of(" "));
		
		int x1,x2;
		x1 = stoi(strs[0]);
		x2 = stoi(strs[1]);
		//sscanf(&strs[1], "%d", &x2);
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
	//cout<<"make list"<<x<<endl;
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

	//cout<<x1<<" and "<<x2<<endl;
	vector<int> parent_x1 = get_all_parents_for_one_node(x1, parent_map);
	vector<int> parent_x2 = get_all_parents_for_one_node(x2, parent_map);

	int i = parent_x1.size()-1 , j = parent_x2.size()-1 ;
	//cout<<"LCA"<<endl;
	int lca = 1;
	while (i>=0 && j>=0){
		//cout<<parent_x1[i]<<" ? == "<<parent_x2[j]<<endl;	
		if(parent_x1[i] != parent_x2[j])
			break;
		
		lca = parent_x1[i];

		i--;
		j--;
		//cout<<i<<", "<<j<<endl;

	}
	
	//cout<<"end LCA"<<endl;
	return lca;

}

//==============================
bool isParam(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

//===============================
int main(int argc, char **argv){

	map<int,int> data_taxonomy_parent = read_file_with_2_element(argv[1]);
	map<int,int> data_nodeID_taxID = read_file_with_2_element(argv[2]);
	
	FILE* fp = fopen(argv[3], "r");
	if (fp == NULL)
                exit(EXIT_FAILURE);

        char* line = NULL;
        size_t len = 0;

	string output="";

	cout<<"start lca!"<<endl;
        while ((getline(&line, &len, fp)) != -1) {

                vector<string> strs;
                boost::split(strs,line,boost::is_any_of(" "));
		
		if(isParam(strs[0]) == false)
			continue;
		//cout<<strs[0]<<endl;
                int lca = stoi(strs[0]);
		lca = data_nodeID_taxID[lca];
		
                for (int i = 1; i< strs.size(); i++){
                        //cout<<"size:"<<strs.size()<<i<<" : "<<strs[i]<<endl;	
			
			if(isParam(strs[i]) == false)
                        	continue;
			int temp = stoi(strs[i]);

			lca = LCA(lca, data_nodeID_taxID[temp], data_taxonomy_parent);
			if(lca == 1)
				break;

                }// end for : find lca
		
		//cout<<lca<<endl;
                output +=to_string(lca)+"\n";

        }// end file read lines
        fclose(fp);
        if (line)
                free(line);


	cout<<"write lca kmers"<<endl;

        std::ofstream out1 ("output_lca_kmers.txt",std::ofstream::out);
        out1 << output;
        out1.close();

	return 0;



}//end main

