## Moving Forward

So now that we have implemented our own "class" in C, we have demonstrated the 
paradigm of abstraction in the object orientated design philosophy model. This is not enough
however, and I will quickly go over why some issues with out implementation require that
the other three paradigms be implemented as well.

#### Polymorphism

Our string class implementation was fine, however, it does seem a bit awkward to have to
declare a "new_class" function and a "delete_class" function for every single class we 
design. It would be easier on the programmer to not have to remember all these individual
class implementations and instead just call new(class_name). This could either return a 
valid object, or return an error if a class of this type has not been implemented. You
might think that this sounds like another layer of abstraction, instead of polymorphism. 
You would be correct, but implemented this layer of abstraction requires polymorphic
methods after all. This is because for every class, there must still be a class
creating method that new(class_name) must call. These all must be uniform as well, so that
new(class) will know where to look. In a sense, these will be polymorphic methods because
they should all have the same name, but do very different things.

#### Inheritance

The next issue with our implementation is that our string class is very static. Say for 
example that we wanted to make an IP address class, and implement methods such as
convert to network representation and back. This class could utilize several methods
from our string class, but the issue is that we would either have to implement these
redundant methods in the IP address class, or implement our IP address class methods
in the string class, where very few objects would actually utilize them. The best solution
is to inherit these methods from the string class, and add on the additional functionality
needed to implement our IP address class.

#### Encapsulation 

The lass issue with our class is that any object and access any other objects data
and methods. What if, for example, instead of writing this:

```
string_1->free(string_1)
```

the programmer wrote this:

```
string_1->free(string_2)
```

As of right now, our implementation has no issue with this call, and will willingly
execute it, freeing string 2, through string_1's method. There should be some sort of 
guard in place in order to protect an object's data and methods from outside access. 
Therefore we need to implement some for of encapsulation in our classes.