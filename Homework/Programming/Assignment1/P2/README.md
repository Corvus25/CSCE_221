# Assignment 1 P2 – A Collection Class

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 2/4/2020

### Resources
- N/A - Some "Stack Overflow" sites to reference some syntactical C++ stuff.

### Known Issues
- N/A

### Description
This program implements a collection for organizing data and for performing oeprations on this data. Specifically, it
generates a collection of stress balls of various colors and sizes, in no particular order. The program then compares
stress balls against each other to check for equality. Stress balls are equivalent if they share the same size & color
traits. Additionally, these Stress balls are placed into various Collections, where the collections can be sorted by
various algorithms, copied, moved, emptied, appended to or removed from, resized, compared against each other, and so on.


### Testing
Building on the original Stress_ball assignment, this part of the assignment focuses on the implementation of Collection
objects which contain Stress_balls. It is assumed that the testing for part 1 of this assignment has already occured.
The Collection class and its objects are tested mainly in ```Collection_test.cpp```. The program goes about executing
various parts of the Collection class, testing all the required functions by comparing the output of variables before and
after they are affected by each function.

####Exceptions
Exceptions are thrown in this program using ```throw``` to indicate a fatal error that would cause the program to error out.
This shouldn't happen given the provided ```stress_ballX.data``` files, but the exceptions are provided in case new files
are introduced. Exceptions are thrown in the following places:
- ```Stress_ball Collection::remove_any_item()```
    - An item cannot be removed if the Collection is empty.
- ```void Collection::remove_this_item(const Stress_ball& sb)```
    - An item cannot be removed if the Collection is empty.
- ```Stress_ball &Collection::operator[](int i)```
    - Index out of bounds exception 
- ```const Stress_ball &Collection::operator[](int i) const```
    - Index out of bounds exception
- ```void sort_by_size(Collection &c, Sort_choice sort)```
    - ```default``` case for when the selected ```Sort_choice``` does not exist.
