**Relevant Files:**

* / lib / src / string_class.c 
* / lib / include / string_class.h 
* / test / test_1.c 

## Object Example

This section will be dedicated to the OOD paradigm of abstraction. 
Abstraction is, in short, the isolation and generalization of functionality.
Now, this is a broad definition to say the least. In terms of object 
oriented design, abstraction is the way that the implementation of 
commonly used routines are isolated to one class, and generalized 
so that any object of this type can use these routines without having 
to worry about the details of the implementation.


Before we go further, I think it is best if I went through a very
quick demonstration of how to implement a class in C and abstract away
the functionality of this class. With function pointers, we can replicate 
the extreme barebones of object orientated behavior. Once we have done that, 
it will be plain to see how this implementation is impractical, and how 
we can improve this into something much more usable.


So in order to demonstrate a barebones implementation of what is often thought
of as a primitive type but is actually a class; the string. Since many 
programmers coming from a higher level language like Python find static arrays,
malloc calls, free calls, etc cumbersome to work with, implementing a barebones
string class can also be a practical exercise.


One of my professors once told me that all programming was wrapping code
around an environment. So, a good place to store our environment is a
struct. All we know so far is that our string class should contain some 
letters representing the string.

```
typedef struct string string_t;
struct string{
    char * char_string;
    size_t len;
};
```

Nothing too fancy so far. We are declaring the string type, string_t as a 
pointer since it should never be dereferenced. However, we still have some 
functionality to add.The first thing that we can abstract away is declaring 
a new string. Let's define a function to do this for us. Our new_string 
function is going to act like a constructor; we are going to pass it arguments and it will construct
the class around those arguments. Therefore, our new_string function should 
take in a string representing the string we want stored in our class.

```
string_t new_string(char * _string, size_t _size) {
    string_t self = malloc(sizeof(string_t));
    char *self_string = malloc(_size+1);
    memcpy(self_string, _string, _size);
    self->char_string = self_string;
    self->len = _size;
    return self;
}

```

Again, nothing to fancy here. We are not simply setting the 
string_t->char_string to point towards the string that we received in the 
function because this string might not always be declared on the heap,
it could be a local array. In this way, we can free our string as needed
without worrying about adversely affecting other parts of the program. Now,
declaring a string looks like this:

```
string_t string_1 = new_string("ABCDEFG", 7);
```

And accessing our string looks like this:

```
string_1->char_string
```

So far, haven't improved over simply malloc'ing memory for a static character
array so let's add some additional functionality. One thing that every
C programmer hates is extending a string, so it would be nice if our
string class would cover that for us. Our method should take in the 
additional characters that should be added on, as well as the size of those
characters. The declaration could look like this:

```
void _extend(const char * _string, size_t _size){}
```

Now, you may notice an issue here. We never told this function *which* string
to extend. That's right, even though this function will become an object 
method, it will have no idea what object it is working on unless we directly
specify which object we want extended. This is a little quirk of object
oriented programming that is frequently hidden from the programmer. For
example, in both C++, and Java, the "this" keyword is a pointer to a current
object. In these languages, you do not need to pass around a pointer to the
current object as the language itself does that for you. In Python, the 
"self" keyword is used, and this is why self *must* be passed to every class
method in python. So let's add the object to our function declaration.

```
void _extend(string_t self, const char * _string, size_t _size){}
```


Now we get back to function pointers. Let's declare a function pointer to 
this function, and store it in our string_t struct. 

```
typedef struct string string_t;
struct string{
    char * char_string;
    size_t len;
    void(*extend)(string_t,const char*,size_t);
};
```

So if you were wondering why I put an underscore before the original declaration
of extend, it is to distinguish between the function itself, which should
never be used by the programmer, and the function pointer, which should be 
used by the programmer through the string class. Our "new_string" function
needs to be modified as well, in order to set the extend function pointer 
to point towards to the extend function.

```
string_t new_string(char * _string, size_t _size) {
    string_t self = malloc(sizeof(string_t));
    char *self_string = malloc(_size+1);
    memcpy(self_string, _string, _size);
    self->char_string = self_string;
    self->len = _size;
    self->extend = &_extend;
    return self;
}

```

Now we can actually go about implementing this function. 

```
void _extend(string_t self, const char* _string, size_t _size){
    if ((self->char_string = realloc(self->char_string, self->len + _size+1)) != 0){
        memcpy(self->char_string + self->len, _string, _size);
        self->len+=_size;
    }
}
```

With our method fully implemented, we can extend our string like this:

```
string_1->extend(string_1, "HIJKLMNOPQRSTUVWXYZ", 19);
```

Our string now contains "ABCDEFGHIJKLMNOPQRSTUVWXYZ".

Along with extend, I have implemented several other string methods. extendl
takes the self pointer, a string, and a size and adds it to the left side 
of the char string. Index takes the self pointer, and a character, and will
return the index of the element if it is found in the char string, or -1 if
it is not. Slice acts very similar to a Python slice, it takes the self 
pointer, a left index, and a right index, and slices the char string based 
on those indexes. str_eq takes the self pointer, and a pointer to another
string_t object and compares and will return true if their char strings are
identical or false if otherwise. replace takes the self pointer, a 
character value, an integer representing the number of following arguments, 
and a variable number of arguments representing characters to be replaced
by the character value given in the second argument. Lastly, dest will 
destroy the object and free all memory being used. Check outall of these 
functions in use in the file /test/test_1.c .

On a side note, I know that string_1->char_string is a very verbose command
in order to access the char string. This is more done for readability than
practicality. Feel free to change the variable and type names to something 
easier to work with such as s->cs .