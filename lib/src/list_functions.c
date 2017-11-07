#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "list_functions.h"


void map(void(*f)(void*), void * data, size_t data_bytes, size_t data_length) {
    for (char * i = (char*)data; i < (char*)data + (data_length*data_bytes); i += data_bytes) {
        f(i);
    }
}

void filter(int(*f)(void*), void*data, size_t data_bytes, size_t data_length){
    char * result = malloc(data_bytes * data_length);
    char * curr_pointer = result;
    for (char * i = (char*)data; i < (char*)data + (data_length*data_bytes); i += data_bytes) {
        if (f(i)) {
            memcpy(curr_pointer, i, data_bytes);
            curr_pointer+=data_bytes;
        }
    }
    memcpy(data, result, (size_t) (curr_pointer-result));
    (*((char*)data + (size_t) (curr_pointer-result))) = 0x0;
    realloc(data, (size_t)(curr_pointer-result) + 1);
}

unsigned int reduce(unsigned int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length){

    unsigned int result = f(data, data+data_bytes);
    if(data_length == 2){return result;}
    unsigned int * return_var = &result;
    for(char * i = (char*)data + (2*data_bytes); i < (char*)data+(data_length * data_bytes); i+=data_bytes){
        result=f(return_var, i);
    }

    return result;
}

void heapify(int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length, int root){
    int max = root;
    int child = (2*root) + 1;
    while(child < data_length) {
        if (child+1 < data_length &&
            f(data + (data_bytes*(child+1)), data + (data_bytes* child))){
            child+=1;
        }

        if(f(data + (data_bytes*child), data+(data_bytes*root))){
            max = child;
        }
        if (max == root) {
            break;
        }
        char *temp_block = malloc(data_bytes);
        memcpy(temp_block, data + (max * data_bytes), data_bytes);
        memcpy(data + (max * data_bytes), data + (root * data_bytes), data_bytes);
        memcpy(data + (root * data_bytes), temp_block, data_bytes);
        free(temp_block);
        root = child;
        child *=2;
    }
}

void sort(int(*f)(void*,void*), void*data, size_t data_bytes, size_t data_length) {
    for (int i = (data_length/2)-1; i >= 0; i--) {
        heapify(f, data, data_bytes, data_length, i);
    }

    for (size_t i = data_length-1; i >= 1; i--) {
        char *temp_block = malloc(data_bytes);
        memcpy(temp_block, data, data_bytes);
        memcpy(data, data + (i*data_bytes), data_bytes);
        memcpy(data + (i*data_bytes),temp_block, data_bytes);
        heapify(f, data, data_bytes, i, 0);
    }

}
