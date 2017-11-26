#ifndef C_OBJECTS_VECTOR_CLASS_H
#define C_OBJECTS_VECTOR_CLASS_H
#include "class.h"

//extern base_class * vector;
void * vector_constructor(base_class * _self, va_list * args);
void vector_destructor(void * self);

typedef struct vector_struct vector_t;
struct vector_struct {
    base_class * self_base;
    size_t elem_len;
    size_t num_elems;
    char * elem_vector;
};

#endif
