


using namespace std;

template<typename IteratorType>
void insertSort(IteratorType first, IteratorType last)
{
    IteratorType a = first;
    IteratorType b = first;
    IteratorType mini = first; //counter
    while(a < last){
        a = mini;
        b = a;
        while (b < last){
            if( *b < *mini){
                mini = b;
            }
            ++b;
        }
        swap (*mini, *a);
        ++b;
    }

}
