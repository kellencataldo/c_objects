#ifndef C_OBJECTS_CLASS_H
#define C_OBJECTS_CLASS_H
#include <stddef.h>
#include <stdarg.h>
#include "string_class.h"

//BEGIN BASE CLASS
struct base_class {
    size_t size;
    void * (* constructor) (void * self, va_list * app);
   // void * (* dtor) (void * self);
  //  void * (* clone) (const void * self);
   // int (* differ) (const void * self, const void * b);
};
void * new (const void * _class, ...);
//END BASE CLASS


//BEGIN CLASS IDENTIFIERS
extern const void * string;


#endif //C_OBJECTS_CLASS_H
