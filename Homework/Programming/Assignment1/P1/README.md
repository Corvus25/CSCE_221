# Assignment 1 P1 – A Collection Class

* Sean Wangnick
* 427003718
* CSCE 221-505
* swangnick
* swangnick@tamu.edu

### Aggie Honor Statement
I certify that I have listed all the sources that I used to develop the solutions and code to the submitted work.
On my honor as an Aggie, I have neither given nor received any unauthorized help on this academic work.

Sean Wangnick - 1/13/2020

### Resources
- http://www.cplusplus.com/reference/map/map/

### Known Issues
- None

### Description
This program implements a collection for organizing data and for performing oeprations on this data. Specifically, it
generates a collection of stress balls of various colors and sizes, in no particular order. The program then compares
stress balls against each other to check for equality. Stress balls are equivalent if they share the same size & color
traits.

### Testing
The ```Stress_ball``` default constructor generates stress balls of random size and color using the ```std::rand```
function. The program uses this to generate 5 random stress balls. It then generates two stress balls of set size and
color. The program then compares stress balls with ```operator==```, which will return equal only if the color
and size of the stress balls are equal. This successfully tests for correctness because the stress balls are randomly
generated, then compared against stress balls of set size and color. Error handling is not required for this program, as
there is no chance for error during process of stress ball generation, comparison, or output.