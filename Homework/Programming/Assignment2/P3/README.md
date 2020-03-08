# Assignment 2 P3 – MinQueue

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 3/6/2020

### Resources
- Dr. Leyk's slides

### Known Issues
- Runner file is expected to fail on the last test case, to show the result of attempting to find the minimum element on an empty queue.

### Description
The MinQueue data structure is based on the Templated DLList from Part 2.

### Testing
The underlying functionality and correctness of this program can be guaranteed by the correct implementation of the
Templated Doubly Linked List from Part 2.

Running time of all functions (excluding `min()` and size operations) is `O(1)`, as each function is only executing a single operation
(in terms of `class LinkedQueue`). `is_empty()` checks if the doubly linked list is empty. `enqueue()` inserts an element
at the end of the doubly linked list. `dequeue()` removes the first element of the doubly linked list. `size()` simply returns the size. 
Several of these functions require multiple operations within `class TemplatedDLList` to do the actual relinking steps in the DLL, they only
require a single step in this `MinQueue` scope.
`min()` requires `O(n)`, since the entire doubly linked list (or queue) must be traversed in order to find the minimum element.

#### Exceptions
Only one exception is needed for this program, which is thrown when it is determined that the queue is empty, and a call
to `min()` or `dequeue()` is called.