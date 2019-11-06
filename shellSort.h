#include <stdio.h>
#include <vector>
#include <cmath>

template <typename IteratorType>
void shellInsertionSort( IteratorType first, IteratorType last, size_t n ){
	IteratorType j;
	for ( auto i = first + n ; i < last ; i += n ){
		j = i;
		while ( j != first ){
			if ( *(j-n) > *j ){
				swap( *j, *(j - n) );
				j -= n;
			} else break;
		} 
	}
}

template <typename IteratorType>
void shellSort(IteratorType first, IteratorType last){
	size_t size = distance( first, last );
	std::vector<size_t> jumps;
	size_t current = 1;
	int k = 1;
	while ( current < size ){
		jumps.push_back(current);
		current = pow( 2, k ) + 1;
		++k;
	}

	for ( size_t i = jumps.size(); i > 0; --i) {
		shellInsertionSort<IteratorType>( first, last, jumps[i-1] );	 
	}
}	


