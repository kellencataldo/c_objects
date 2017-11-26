#include <stdio.h>
#include <stdlib.h>

#include "vector_class.h"
#define DEFAULT_SIZE 10

static base_class _vector = {
        vector_constructor,
        vector_destructor,
        sizeof(vector_t)
};
base_class * vector = &_vector;

void * vector_constructor(base_class * _self, va_list * args) {
    vector_t *self = (vector_t *) _self;
    self->elem_len = va_arg(*args, const size_t);
    self->num_elems = 0;
    self->elem_vector = malloc(DEFAULT_SIZE * self->elem_len);
    return self;
}

void vector_destructor(void * self){}

