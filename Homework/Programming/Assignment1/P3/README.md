# Assignment 1 P3 – A Collection Class

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 2/16/2020

### Resources
- Some "Stack Overflow" sites to reference some syntactical C++ stuff.
- A lot of Piazza posts to clear up confusion about the assignment.

### Known Issues
- N/A

### Description
As an extension of Parts 1 and 2 of this assignment, Part 3 implements a templated version of the Collection class,
bringing with it the ability to handle more objects besides stress_balls. This is tested with the Jeans class.


### Testing
Building on the original parts of this assignment, it is assumed all testing related to previously defined functions is
already complete. The only testing really required for Part 3 is the correct implementation of class templating, which
is done with the Jeans class.

#### Exceptions
From Part 2:

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
    
Further exceptions are not needed for the templating implementation, as the tests are hard coded and cannot error out.
However, exceptions could be implemented in the case that new objects are created with sizes or colors that are not 
included in the current enumerated size and color classes for those objects.

---

Templating allows class code to become more flexible and apply to broader subjects. In this case, the lack of templating
would have resulted in a code rewriting in order for the Collection's members to work with different objects. Templating
the Collection class allowed it to be applicable to any object that is structured similarly to stress ball's or jeans,
in the sense that they can still be added to a Collection, and be acted upon by the class's members like a stress ball
would. 