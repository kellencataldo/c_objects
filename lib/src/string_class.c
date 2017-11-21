#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include "string_class.h"


static struct base _string = {
        string_constructor,
        string_destructor,
        sizeof(struct string_struct)
};

base_class string = &_string;

void * string_constructor(base_class _self, va_list * args) {
    string_t self = (string_t) _self;
    const char * base_string = va_arg(* args, const char *);
    self->len = va_arg(* args, const size_t);
    self->char_string = malloc(self->len + 1);
    memcpy(self->char_string, base_string, self->len);
    *(self->char_string + self->len) = 0x0;
    self->extend = _extend;
    self->extendl = _extendl;
    self->index = _index;
    self->slice = _slice;
    self->replace = _replace;
    self->str_eq = _str_eq;
    return self;
}

void string_destructor(void * self){
    free(((string_t) self)->char_string);
    free(self);
}

void _extend(string_t self, const char* _string, size_t _size){
    if ((self->char_string = (char*)realloc(self->char_string, self->len + _size+1)) != 0){
        memcpy(self->char_string + self->len, _string, _size);
        self->len+=_size;
        *(self->char_string + self->len) = 0x0;
    }
}

void _extendl(string_t self, const char* _string, size_t _size){
    char * new_string = (char*)malloc(self->len+_size + 1);
    if (new_string !=  NULL) {
        memcpy(new_string, _string, _size);
        memcpy(new_string + _size, self->char_string, self->len);
        free(self->char_string);
        self->char_string = new_string;
        self->len += _size;
        *(self->char_string+self->len) = 0x0;
    }
}

int _index(string_t self, char a){
    for(size_t i = 0; i < self->len; i++ ){
        if(a == *(self->char_string + i )){
            return (int)i;
        }
    }
    return -1;
}

void _slice(string_t self, size_t left, size_t right){
    if (left > self->len || left > right){ return;}
    if (left == 0 && realloc(self->char_string, right+1) != 0){ return;}
    else{
        char*new_string = (char*)malloc(1 + right - left);
        if(new_string != NULL) {
            memcpy(new_string, self->char_string + left, right - left);
            free(self->char_string);
            self->char_string = new_string;
            *(new_string+(right-left)) = 0x0;
            self->len = right - left;
        }
    }
}


void _replace(string_t self, char a, int nargs, ...){
    va_list list;
    for(size_t i = 0; i < self->len; i++){
        va_start(list, nargs);
        for(int arg=0; arg < nargs; arg++){
            if (*(self->char_string+i) == va_arg(list, int))  {
                *(self->char_string + i) = a;
            }
        }
        va_end(list);
    }
}

int _str_eq(string_t self, string_t other){
    if( self->len != other->len){ return 0;}
    else{
        for(size_t i = 0; i < self->len; i++){
            if (*(self->char_string+i) != *(other->char_string+i)) {return 0;}
        }
    }
    return 1;
}
