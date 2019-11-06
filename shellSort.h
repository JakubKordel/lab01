#include <stdio.h>

template <typename IteratorType>
void shellInsertionSort( IteratorType first, IteratorType last, int n ){
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
	size /= 2;
	while ( size > 1) {
		shellInsertionSort<IteratorType>( first, last, size );
		size /= 2;		 
	}
	shellInsertionSort<IteratorType>( first, last, 1 );
}	


