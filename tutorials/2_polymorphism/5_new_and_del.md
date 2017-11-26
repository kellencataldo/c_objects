**Relevant files:**
* / lib / src / class.c 
* / lib / include / class.h 
* / lib / src / vector_class.c 
* / lib / include / vector_class.h 
* / test / test_2.c 



## Defining a "new" and "del" function

This section will cover how we will implement both a "new" and "del" function and how both of
these methods relate to our polymorphic design principle. First, lets explore some ways that 
we could implement our "new" function and the issues with each of these. 

With our string class example our implementation had its own constructor and its own 
destructor. However, we want our "new" method to work for all classes. Ideally, we want our 
method to take a description of the class, any arguments that we need to feed to the 
constructor, and return a pointer to the created object. The most straightforward 
way that we could accomplish giving each class an integer type descriptor and chaining
together a bunch of "if" statements which would execute different constructor methods
depending on the type descriptor provided. There are several issues with this 
implementation however. The first as that it would be a mess to look at, and required the 
programmer to either memorize the type descriptors, or define macros and assign them to
the corresponding type. 

A second more subtle issue is that this would require that the base class file either
contain all class implementations itself, or #include every single other file containing
the class implementation. This would require the programmer to #include a potentially 
huge amount of files that they may not need or want. This is why in Java one does not
import the base class file, and instead imports a class implementation (which in turn 
imports the base class). Instead, our solution should be the other way around: any class
file should be required to #include the base class file and be responsible for their own
constructors, destructors, etc.

The solution was touched upon briefly in the previous tutorial. We will implement a base 
class that all classes will inherit. Instead of one big long "if" block, our "new" function
will consult the constructor and destructor in the base class of an object to both build
and destroy the object.

Let's define our base class as it should appear in class.h:

```
typedef struct base base_class;
struct base {
    void*(* constructor) (base_class*, va_list*);
    void(*destructor)(void*);
    size_t size;
};

```

Now, lets define a new class that we can put this base_class into. A vector class,
mimicking the C++ STL container implementation would be useful to have in C.


```
typedef struct vector_struct * vector_t;
struct vector_struct {
    base_class * self_base;
    size_t elem_len; //size in bytes of individual elements
    size_t num_elems; //number of individual elements
    char * elem_vector; //element container
};
```

Now we can define a base class for our static vector structure in vector_class.c:

```
static base_class _vector = {
        vector_constructor,
        vector_destructor,
        sizeof(base_class)
};
base_class * vector = &_vector;
```

There are a couple of things to notice here. The first is that our structure was
declared static. This because this structure should not be visible to any other file.
Every time "new" is called, it should consult this base_class when it needs to construct
any and all vectors. The way it reaches this base_class is through our pointer "vector".
This means that any and all vectors declared with "new" will contain a pointer to the
exact same base class. Access to this pointer is declared in the vector_class.h file:

```
extern base_class * vector;
```

Now, let's now define our "new" function and walk through it line by line.

```
void * new (base_class * _class, ...) {
    void * new_class = malloc(_class->size);
    *(base_class **) new_class = _class;
    va_list args;
    va_start(args, _class);
    new_class = _class->constructor(new_class, &args);
    va_end(args);
    return new_class;
}

```

The first line contains some uncommon syntax. The ellipsis defines a macro that allows
functions to receive a variable amount of arguments. printf, for example, makes use
of this macro as it could take any number of percent codes. It is used here because
the classes that we define could required any number of arguments to be passed to the 
constructor. Our vector class will only take one: the size of the elements to be 
stored. 

The next line:

```
    void * new_class = malloc(_class->size);
```

is fairly straight forwards. However, one thing to remember is that this "size" 
variable is not the size of the base_class itself. It contains the size of the 
class structure to be made. 


This line:

```   
    *(base_class **) new_class = _class;
``` 

is where things start to get really interesting. Recall that our "new" function has 
no idea what type of object it is creating. However, what "new" does know, is that
every single object created will point to the base_class that it has been passed.
A structure is simply sequential memory and casting a pointer to a structure is the 
exact same thing as casting a pointer to the structure's first element. This is
what our "new" function does. The first element of every class structure is a 
pointer other base_class. So our "new" function treats the pointer to our new_class 
as a pointer to a pointer to a base class. It dereferences this pointer to the 
new_class and sets the base_class pointer to point to the base_class that has
been provided in the arguments. Now, if you have looked ahead, you may notice that
"new" never accesses the base_class through the object. Giving an object access to 
its own base_class is for the benefit of our other class methods. Our del function 
will make use of this pointer.

The rest of the lines:

```
    va_list args;
    va_start(args, _class);
     _class->constructor(new_class, &args);
    va_end(args);
    return new_class;
```

need little explanation. va_list initializes the argument list. The constructor
is then called and the arguments are passed to it. Now, we can move onto the 
vector constructor itself.

