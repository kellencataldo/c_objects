#### Polymorphism

Polymorphism is next on our list of features to implement in our object oriented C
library. Polymorphism is essentially one interface, many types. Programmers interact
with polymorphic methods all the time without even realizing it. Yes, even C programmers
do as well. For example this piece of code: 

```
    size_t var1 = 1;
    int var2 = 2;
    long long var3 = var1+var2;
```

is perfectly valid and compiles without warning. Yes, that is polymorphism. 
Notice how, despite operating on two different types, and returning a third type,
the "+" operator has no issue with this statement.  This many-types one-interface
behavior is polymorphism. 

Every single class in all programming languages implement some form of polymorphism.
This is because all classes inherit some base class. You could even declare a class
in Python and implement no methods or variables, and it would still inherit the base
class and implement polymorphic behavior.

Why is this? Because there are methods common to all classes. These implementations are 
mostly hidden from the programmer in other languages though. These include a constructor
which declares the object and allocates resources for that object. A destructor, which
frees all the resources allocated for that object. Some sort of comparison mechanism 
between objects. Some sort of copy mechanism between objects. These are just a few of 
them. Some languages implement more, but not all languages implement them the same way.

Now, we are working in C, so we will have to implement them all ourselves. But we can
simplify usage for the next person to use our code. The way we can do this is by 
implementing some sort of base class which has uniform polymorphic methods that can 
be utilized by all of our classes. For example, what if instead of having a separate 
constructor for every class, we had one "new" method that could work for all types. 
This idea is what we will be working on next.