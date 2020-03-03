# Assignment 2 P1 – Doubly Linked List

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 2/17/2020

### Resources
- Some "Stack Overflow" sites to reference some syntactical C++ stuff.
- Previous work from CSCE 121 DLL homework, including the `to_str()` function.
- Dr. Leyk's DLL slides.

### Known Issues
When `make`ing the executable, the compiler throws warnings referring to a dereferenced pointer being compared to
`nullptr`:

>warning: reference cannot be bound to dereferenced null pointer in well-defined C++ code; comparison may be assumed to
>always evaluate to false

However, the executable still compiles fine and this does not affect the behavior of the program; thus, for the purpose
of this assignment, does not warrant a fix.

### Description
This implementation of a Doubly Linked List class does pretty much exactly what the name suggests. A `DLList` class
is defined by functions that allow the instantiation, copying, moving, and traversal of a Doubly Linked Lists. The
nodes of the DLL are defined by the struct `DLListNode`, which defines an object to store, and pointers to the
previous and next node. This implementation of the DLL and its nodes only support data of type `int`.

### Testing
The DLL implementation is tested by the functions in `DLList-main.cpp`. Various tests are performed to verify the
correctness of the implementation, including (but not limited to) creating an empty list, adding nodes, removing nodes,
copying and moving to other lists via the constructors and assignment operators, inserting and removing before and after
in various positions to show that the `next` and `prev` pointers remain consistent in every case, and traversing
backwards.

#### Exceptions
Additional exceptions were added simply to have the ability to differentiate between different types of DLL errors.
- `EmptyDLList` - thrown when an attempted operation on a list would be invalid because it is empty. 
- `InvalidInsertion` - thrown when the insertion of a node would be out of bounds of the DLL.
- `InvalidRemoval` - thrown when the removal of a node would be out of bounds of the DLL.
- `PointerInvalid` - thrown when the pointer at hand does not exist, and thus cannot be acted upon by the function.