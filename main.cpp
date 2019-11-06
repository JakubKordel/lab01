#include <iostream>
#include "shellSort.h"
#include <fstream>
#include <vector>

int main(){
	std::vector<std::string> data;
	std::ifstream file;
	file.open("text");
	std::string word; 
	while (file.good()){
		file >> word;
		data.push_back(word);
	}
	file.close();
	shellSort<std::vector<std::string>::iterator>( data.begin(), data.end() );
	std::ofstream output;
	output.open("output.txt");
	for ( size_t i = 0 ; i < data.size() ; ++i ){
		output << data[i] << std::endl;	
	}
	output.close();
	return 0;
}
