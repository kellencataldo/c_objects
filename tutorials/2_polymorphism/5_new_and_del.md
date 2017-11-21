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

