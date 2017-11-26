#ifndef C_OBJECTS_CLASS_H
#define C_OBJECTS_CLASS_H
#include <stddef.h>
#include <stdarg.h>

typedef struct base base_class;

struct base {
    void*(* constructor)(base_class*, va_list*);
    void(*destructor)(void*);
    size_t size;
  //  void * (* clone) (const void * self);
};
void * new (base_class * _class, ...);
void del(void * _class);

#endif
