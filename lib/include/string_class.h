#ifndef C_OBJECTS_STRING_CLASS_H
#define C_OBJECTS_STRING_CLASS_H

#include "class.h"

extern base_class * string;
void * string_constructor (base_class * _self, va_list * args);
void string_destructor(void * self);

typedef struct string_struct string_t;
struct string_struct {
    base_class * self_base;
    char * char_string;
    size_t len;
    void(*extend)(string_t*,const char*,size_t);
    void(*extendl)(string_t*, const char*, size_t);
    int(*index)(string_t*, char);
    void(*slice)(string_t*, size_t, size_t);
    int(*str_eq)(string_t*, string_t*);
    void(*replace)(string_t*, char,int, ...);
};

void _extend(string_t * self, const char* _string, size_t _size);
void _extendl(string_t * self, const char* _string, size_t _size);
int _index(string_t * self, char a);
void _slice(string_t * self, size_t left, size_t right);
int _str_eq(string_t * self, string_t * other);
void _replace(string_t * self, char a, int nargs, ...);

#endif//C_OBJECTS_STRING_CLASS_H