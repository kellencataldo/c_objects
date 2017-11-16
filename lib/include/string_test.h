#ifndef C_OBJECTS_STRING_TEST_H
#define C_OBJECTS_STRING_TEST_H

#include <stdarg.h>

struct string {
    const void * class; /* must be first */
    char * char_string;
    size_t len;
    void(*extend)(string_t,const char*,size_t);
    void(*extendl)(string_t, const char*, size_t);
    int(*index)(string_t, char);
    void(*slice)(string_t, size_t, size_t);
    int(*str_eq)(string_t, string_t);
    void(*replace)(string_t, char,int, ...);
    void(*dest)(string_t);
};

void _extend(string_t self, const char* _string, size_t _size);
void _extendl(string_t self, const char* _string, size_t size);
int _index(string_t self, char a);
void _slice(string_t self, size_t left, size_t right);
int _str_eq(string_t self, string_t other);
void _replace(string_t self, char a, int nargs, ...);
void _dest(string_t self);

#endif //C_OBJECTS_STRING_TEST_H
