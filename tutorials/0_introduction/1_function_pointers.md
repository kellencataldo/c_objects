**Relevant files:** 
* / lib / src / list_functions.c
* / lib / include / list_functions.h
* / test / test_0.c

## Function Pointers

Now, I will assume that you are pretty familiar with 
pointers. So I will use this as a start point.
 If you know what this next expression does, feel free to 
 skip this section.

```
 char*(*f_ptr)(char*,int) = func;
```

This is a function pointer and it does exactly what it sounds like, 
it points to a function. To get more specific, this function pointer 
points to the location of a function (func) that takes a char pointer 
(char\*) and an int (int) and returns a char pointer (char\*). 
A more simple example looks like this statement below. 

```
type (*func_pointer)(type, type)
```

The function declaration of the function that this function pointer 
is pointer to would look like this statement below.

```
type func(type arg_1, type arg_2 );
```

Now, the obvious question is: when would you ever need to use a 
function pointer. Well, one example is that they can be passed to 
other functions. For example, in python one can apply a function to 
every element in the list using the "map" function. The syntax for 
this is shown below.

```
map(function_to_apply, list_of_inputs)
```

We can replicate this function in C, since function_to_apply 
is simply a function pointer (although pointer functionality 
is almost entirely hidden from the programmer in python). 
Let's start with setting up the blueprint for our map 
function. Naturally, it will need a function pointer, and a 
pointer to an array of elements. In order to work on a wide 
variety of data types, I would like to keep the implementation
 of the map function as generic as possible without resorting 
 to GNU preprocessor macros. However, because of this, some 
 aspects of the language are going to get in the way of 
 implementation, and several workarounds are necessary. 
 Put simply, its going to get nasty. 
 
 Lets start with defining our function. We know that it will 
 need to take a function pointer and an array of elements. We want
 the map function to run through a list of elements and then apply a 
 function to that list of elements. We can do this easily using pointer
 arithmetic. 
 
 ```
void map(void(*f)(void*), void * data, size_t data_length){
    for(int * i = data; i < data + data_length; i++){
        f(i);
    }
}
 ```
 
 There is an obvious issue here, which is the fact that this function will
 not have an idea what type it is working. Therefore will not compile
 as pointer arithmetic on a void pointer in C, without casting, is illegal. 
 However, like map in python, it would be nice if this function could 
 work with all sorts of data types.
 
 Another more subtle, but related issue, is that incremented by int will
 not work for all types, such as a list of chars because every increment of 
 int i is four characters long.
 
 The solution is to also add the size of the data, in bytes, to the arguments. Therefore,
 we can simply cast the void pointer as a char pointer (since this is the 
 shortest possible data size) and then perform pointer arithmetic by
 incrementing by the data size. Here is our final function.
 
 ```
void * map(void(*f)(void*), void * data, size_t data_bytes, size_t data_length) {
    for (char * i = (char*)data; i < (char*)data + (data_length*data_bytes); i += data_bytes) {
       f(i);
    }
}
 ```
 
 Now we have solved both problems, and our map function will work on any
 data type. To test this, lets define the function that we want to 
 map to the elements.
 
 ```
void square_func(void*element) {
  *((int*)element) = *((int*)element) * *((int*)element);
}
 ```
 There are a couple things to notice here. The first is that this function is 
 receiving a void pointer. This is necessary if you remember the map function
 was passed a function pointer that looked like this 
 
 ```
void(*f)(void*)
 ```
 
 so that it may work on any data type. The next thing to notice is that we
 are immediately dereferencing that void pointer. Therefore it is up to 
 this function to cast it as an int pointer so that the square operation
 can be performed. In this way, this square function is the only place
 where correct data types must be specified, while the map function
 can remain generic for all types.
 
 Our list of elements will look like this:
 
 ```
 int nums[] = { 1,2,3,4,5 };
 ```
 
 And calling the map function will look like this:
 
 ```
 map(square_func, nums, sizeof(int), 5);
 ```
 
The end result is this:

``` 
nums = { 1,4,9,16,25 };
```
 
 One last thing to mention is that the difference in python between 
 map(func(), list) and map(func, list) is the same difference between calling
 our function as map(square_func_ptr, ...) and map(square_func, ...). In both
 languages, the first version will invoke the call immediately, and the
 second is a pointer to a function which will be used to map every element
 in the list.
 
 Along with map, I have also implemented filter, sort, and 
 reduce in the list_functions.c file. In the file /test/test_1.c I 
 demonstrate how with the use of helper functions and function pointers,
 these functions can be used on most data types. For example:
 map if used to square every int element in an array of ints, but also
 used to capitalize every letter in a string. Filter is used to remove 
 even numbers, but also to remove spaces from a string. Sort is used to 
 sort a list in descending order but also to sort a string by reverse 
 alphabetical order. Reduce is used to sum up the elements in a list, but 
 also to reduce a string representation of a binary integer to that 
 binary value.
 
###### A quick note on syntax:

This statement:

```
 char*(*f_ptr)(char*,int) = func;
```

Is functionally equivalent to this statement:

```
 char*(*f_ptr)(char*,int) = &func;
```

The C standard dictates that the function name "func" is promoted to a function pointer 
when it is passed as an argument, or on the right side of an assignment. Therefore, in
most cases, we don't ever need to declare a separate function pointer to pass as an 
argument to a separate function. However, if you need or want to, it can be done.
The last test in test_0.c demonstrates this implementation. 