#include <assert.h>
#include <mem.h>
#include "string_class.h"

void test_1(){
    string_t string_1 = new(string, "google", 6);
    string_t string_2 = new(string, "https://www.google.com", 22);

    assert(!(  string_1->str_eq( string_1, string_2 )));

    string_1->extend(string_1, ".com", 4);
    assert( strcmp( string_1->char_string, "google.com\0" ) == 0);

    string_1->extendl(string_1, "https://www.", 12);
    assert( strcmp( string_1->char_string, "https://www.google.com\0" ) == 0);

    assert(  string_1->str_eq(string_1, string_2   ));

    assert(string_1->index(string_1, 'l') == 16);
    assert(string_1->index(string_1, 'a') == -1);

    string_1->replace(string_1, ' ', 3, '/', ':', '.');
    assert( strcmp( string_1->char_string, "https   www google com\0" ) == 0);

    string_1->slice(string_1, 12, 18);

    assert( strcmp ( string_1->char_string, "google" ) == 0);

    del(string_1);
    del(string_2);


}