#include <assert.h>
#include <stdlib.h>
#include <mem.h>
#include <stdio.h>
#include "list_functions.h"

//MAP FUNCTIONS
void square_func(void*element) {
    *((int*)element) = *((int*)element) * *((int*)element);
}

void cap_func(void*element){
    if ( (*(char*)element) > 0x60 && (*(char*)element) < 0x7b ) {
        *((char*)element) -=0x20;
    }
}


//FILTER FUNCTIONS
int odd_func(void*element) {
    return (*((int*)element) % 2);
}

int space_func(void*element) {
    return (*((char*)element) != 0x20);
}


//REDUCE FUNCTIONS
unsigned int sum_func(void*element_1, void*element_2) {
    return (*((unsigned int*)element_1) + (*((unsigned int*)element_2)));
}

unsigned int to_bin_func(void*element_1, void*element_2){
    unsigned int result;
    if ( *((unsigned char *) element_1) == 0x31 ) {
        result = 1;
    }
    else if (*((unsigned char *) element_1) == 0x30 ) {
        result = 0;
    }
    else {
        result =  *((unsigned int *) element_1);
    }
    return (result << 1) |  ((*((char*)element_2) - 0x30) );
}


//SORT FUNCTIONS
int sort_func(void*element_1, void*element_2){
    return (  *((int*)element_1) < *((int*)element_2));
}

int alphabet_func(void*element_1, void*element_2){
    char left = *((char*)element_1);
    char right = *((char*)element_2);
    if (left >= 0x61) {
        left -= 0x20;
    }
    if (right >= 0x61) {
        right -= 0x20;
    }

    return left < right;
}


//TEST
void test_1(){

    //MAP TESTS
    void(*square_func_ptr)(void*) = &square_func;
    int * nums_1 = malloc(10*sizeof(int));
    for(int i = 0; i < 5; *(nums_1+i) = i+1, i++);
    int result_1[] = {1,4,9,16,25};
    map(square_func_ptr, nums_1, sizeof(int), 5);
    for (int i = 0; i < 5; i++) {
        assert(nums_1[i] == result_1[i]);
    }

    void(*cap_func_ptr)(void*) = &cap_func;
    char* letters_1 = (char*) malloc(36);
    strcpy(letters_1, "I want this sentence capitalized");
    map(cap_func_ptr, letters_1, sizeof(char), 32);
    assert(strcmp(letters_1, "I WANT THIS SENTENCE CAPITALIZED")==0);


    //FILTER TESTS
    int(*odd_func_ptr)(void*) = &odd_func;
    int* nums_2 = malloc(11*sizeof(int));
    for(int i = 0; i < 10; *(nums_2+i) = i+1, i++);
    int result_2[] = {1,3,5,7,9};
    filter(odd_func_ptr, nums_2, sizeof(int),10);
    for(int i = 0;i<5;i++) {
        assert(nums_2[i] == result_2[i]);
    }


    int(*space_func_ptr)(void*) = &space_func;
    char * letters_2 = (char*) malloc(37);
    strcpy(letters_2, "I don't want spaces in this sentence");
    filter(space_func_ptr, letters_2, sizeof(char),36);
    assert(strcmp(letters_2, "Idon'twantspacesinthissentence")==0);


    //REDUCE TESTS
    unsigned int(*sum_func_ptr)(void*, void*) = &sum_func;
    unsigned int * nums_3 = malloc(5*sizeof(int));
    for(unsigned int i = 0; i < 5; *(nums_3+i) = i+1, i++);
    assert(reduce(sum_func_ptr, nums_3, sizeof(int),5) == 15);


    unsigned int(*bin_func_ptr)(void*, void*) = &to_bin_func;
    char * letters_3 = (char*) malloc(17);
    strcpy(letters_3, "1001010101111010");
    assert(reduce(bin_func_ptr, letters_3, sizeof(char), 16) == 38266);


    //SORT TESTS
    int(*sort_func_ptr)(void*, void*) = &sort_func;
    int * nums_4 = malloc(11*sizeof(int));
    for(int i = 1; i < 11; *(nums_4+i-1) = i, i++);
    int result_5[] = {10,9,8,7,6,5,4,3,2,1};
    sort(sort_func_ptr, nums_4, sizeof(int), 10);
    for(int i = 0; i <10;i++){
        assert(nums_4[i] == result_5[i]);
    }


    int(*alphabet_ptr)(void*, void*) = &alphabet_func;
    char*letters_4 = (char*) malloc(27);
    strcpy(letters_4, "AbCdEfGhIjKlMnOpQrStUvWxyZ");
    sort(alphabet_ptr, letters_4, sizeof(char), 26);
    assert(strcmp(letters_4, "ZyxWvUtSrQpOnMlKjIhGfEdCbA") == 0);


    free(nums_1);
    free(letters_1);
    free(nums_2);
    free(letters_2);
    free(nums_3);
    free(letters_3);
    free(nums_4);
    free(letters_4);
}