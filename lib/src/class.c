#include <stdlib.h>
#include "class.h"

void * new (const void * _class, ...) {
    const struct base_class * this_base = _class;
    void * new_class = malloc(this_base->size);
   //*(const struct base_class **) new_class = this_base;
    if (this_base -> constructor) {
        va_list args;
        va_start(args, _class);
        new_class = this_base->constructor(new_class, &args);
        va_end(args);
    }
    return new_class;
}

static const struct base_class _string = {
        sizeof(struct string),
        string_constructor
};
const void * string = & _string;

