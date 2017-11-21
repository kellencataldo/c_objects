#include <stdlib.h>
#include "class.h"

void * new (base_class _class, ...) {
    base_class this_base = _class;
    void * new_class = malloc(_class->size);
   *(base_class *) new_class = this_base;
    if (_class->constructor) {
        va_list args;
        va_start(args, _class);
        new_class = _class->constructor(new_class, &args);
        va_end(args);
    }
    return new_class;
}

void del(void * _self){
    base_class this_base = *((base_class*) _self);
    this_base->destructor(_self);
    free(_self);
}

