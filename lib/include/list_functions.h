#ifndef C_OBJECTS_LIST_FUNCTIONS_H_H
#define C_OBJECTS_LIST_FUNCTIONS_H_H

#include <stddef.h>


void map(void(*f)(void*), void*data, size_t data_bytes, size_t data_length);

void filter(int(*f)(void*), void*data, size_t data_bytes, size_t data_length);

unsigned int reduce(unsigned int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length);

void sort(int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length);

//FUNCTION PROTOTYPES
// _____ refers to an operation or assignment required


/* MAP FUNCTION PROTOTYPE:

 void map_func(void*element){
   *(type*)element = _____;
}
*/

/*FILTER FUNCTION PROTOTYPE:

int filter_func(void*element) {
    if ( *((type*)element) == ____ ){
    return 1;
    } else {
    return 0;
    }
}
*/


/* REDUCE FUNCTION PROTOTYPE:

unsigned int reduce_func(void*element_1, void*element_2) {
    return (*((type*)element_1) ____ (*((type*)element_2)));
}
*/



/*SORT FUNCTION PROTOTYPE:

int sort_func(void*element_1, void*element_2){
    return (*((type*)element_1) ____ *((type*)element_2));
}
*/
#endif //C_OBJECTS_LIST_FUNCTIONS_H_H
