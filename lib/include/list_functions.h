#ifndef C_OBJECTS_LIST_FUNCTIONS_H_H
#define C_OBJECTS_LIST_FUNCTIONS_H_H

#include <stddef.h>


void map(void(*f)(void*), void*data, size_t data_bytes, size_t data_length);

void filter(int(*f)(void*), void*data, size_t data_bytes, size_t data_length);

unsigned int reduce(unsigned int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length);

void sort(int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length);

#endif //C_OBJECTS_LIST_FUNCTIONS_H_H
