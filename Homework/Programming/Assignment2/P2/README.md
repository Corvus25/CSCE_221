# Assignment 2 P1 – Doubly Linked List

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 2/28/2020

### Resources
- Some "Stack Overflow" sites to reference some syntactical C++ stuff.
- Previous work from CSCE 121 DLL homework
- Dr. Leyk's DLL slides

### Known Issues
When `make`ing the executable, the compiler throws warnings referring to a dereferenced pointer being compared to
`nullptr`:

>warning: reference cannot be bound to dereferenced null pointer in well-defined C++ code; comparison may be assumed to
>always evaluate to false

However, the executable still compiles fine and this does not affect the behavior of the program; thus, for the purpose
of this assignment, does not warrant a fix.

### Description
This implementation of a templated Doubly Linked List class is an extension of the original `DLList`. This version of 
the DLL and its nodes support all relevant data types, even user-defined ones. This simply allows the nodes of the DLL
to contain other data that is not of type `int`.

### Testing
As an extension of Part 1, it is assumed that all relevant testing of the functions is performed in Part 1. The only
additional testing required for the templated implementation is to introduce other data types to fill the nodes.
`TDLList-main.cpp` accomplishes this by testing data of type `string`, and the class continues to function as intended. 

#### Exceptions
The exceptions of the templated class match the exceptions of the untemplated class.

- `EmptyDLList` - thrown when an attempted operation on a list would be invalid because it is empty. 
- `InvalidInsertion` - thrown when the insertion of a node would be out of bounds of the DLL.
- `InvalidRemoval` - thrown when the removal of a node would be out of bounds of the DLL.
- `PointerInvalid` - thrown when the pointer at hand does not exist, and thus cannot be acted upon by the function.