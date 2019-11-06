#include <iostream>
#include "shellSort.h"
#include <fstream>
#include <vector>
#include <sys/times.h>
#include <algorithm>

int main(){
	const int words = 10000;
	std::vector<std::string> data;
	std::ifstream file;
	file.open("text");
	std::string word; 
	while (file.good()){
		file >> word;
		data.push_back(word);
	}
	file.close();
	std::vector<std::string> dataCopy;
	for (int i = 1; i < 11; ++i ){
		dataCopy.assign(data.begin(), data.begin() + i * words );
		struct tms t1, t2;
		times(&t1);
		std::sort<std::vector<std::string>::iterator>( dataCopy.begin(), dataCopy.end() );
		times(&t2);
		auto dt = t2.tms_utime - t1.tms_utime;
		std::cout << std::endl << "std::sort  " << i*words << "words" << std::endl;
		if ( std::is_sorted(dataCopy.begin(), dataCopy.end() ) ){
			std::cout << "Sorted: YES" << std::endl;
		} else std::cout << "Sorted: NO" << std::endl;
		std::cout << "Sorting time: " << dt << std::endl;
	}

	for (int i = 1; i < 11; ++i ){
		dataCopy.assign(data.begin(), data.begin() + i * words );
		struct tms t1, t2;
		times(&t1);
		shellSort<std::vector<std::string>::iterator>( dataCopy.begin(), dataCopy.end() );
		times(&t2);
		auto dt = t2.tms_utime - t1.tms_utime;
		std::cout << std::endl << "Shell Sort  " << i*words << "words" << std::endl;
		if ( std::is_sorted(dataCopy.begin(), dataCopy.end() ) ){
			std::cout << "Sorted: YES" << std::endl;
		} else std::cout << "Sorted: NO" << std::endl;
		std::cout << "Sorting time: " << dt << std::endl;
	}
	return 0;
}
