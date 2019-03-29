# Data-Structures (DS)

## Notices
> "Deque" haven't be completed. 
> Only DS in C++ now. (Maybe I'll add other language's in the future.)
> However, you can store any kind of datatype into my DS. (ex: int, yourClass, otherDSs)

## The Source
These DSs were mostly adapted from the "**Data Structures and Advanced Program Design**" lecture (106-2) which was taught by **CHIEN CHIN CHEN** and **LING-CHIEH KUNG** in National Taiwan University (NTU).
Some details were refined and redesigned.

## Usage
For example, you may want to use "Stack" in your programs.
### First Step: include
You need to copy not only "Stack.h" but "Node.h" into your folder where your file of codes exists (because "Stack.h" needs to include "Node.h" in the same folder). 
Then, add these codes into your own code which needs "Stack".
```C++
// ... your included library
#include "Stack.h"
// ... your other codes
```
You don't need to include "Node.h". (Only when you want to use "Node" itself.)
### Second Step: Use it!
choose the one you like! "LinkedStack" or "ArrayStack"? 
(About the differences, please search it on Google or StackOverflow. Recommend for the former)

and write these where you want to declare "Stack"
```C++
// ...
  LinkedStack<yourDatatype> nameForStack; // use ArrayStack<yourDatatype> if you want
// ...
```
and start use your "Stack"!

For other DS, the steps are the same.
Enjoy the convenience that these DS brings to you!

## Functions
For each DS, please see the DS's "Interface", which is the parent class of all the classes and written in the head of each .h file.

## Appendix
If you have any problems in using my code, feel free to ask me.
Comments and Discusses are also welcome.

Since it's my first time to write README.md, if there's something that this README.md doesn't say or my English is not good enough to let you know how to use, please tell me!

2019.03.30
