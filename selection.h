//
// Created by arsze on 04.11.2019.
//

#ifndef PROGRAMING_AISD_TEMPLATE_H
#define PROGRAMING_AISD_TEMPLATE_H


//
// Created by KejDablju on 04.11.2019.
//

using namespace std;

template<typename IteratorType>
void selectionSort(IteratorType first, IteratorType last)
{
    IteratorType a = first;
    IteratorType b = first;
    IteratorType mini = first; //counter
    while(a < last){
        mini = a;
        b = a;
        while (b < last){
            if( *b < *mini){
                mini = b;
            }
            ++b;
        }
        swap (*mini, *a);
        ++a;
    }
}

#endif //PROGRAMING_AISD_TEMPLATE_H
