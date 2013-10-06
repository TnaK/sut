SUT
===

Simple Unit Test. Minimalistic unit testing framework for c++. Inspired by the remarkably simple [minunit](http://www.jera.com/techinfo/jtns/jtn002.html).
This is a header only library that depends only on minor parts of the c++11 standard library, and is thus easily incorporated into any smaller project written in c++11 or above.

The test executable will return the number of failed tests, so is can be combined with CTest if CMake is used as build enviroment.

Any feedback and pull requests for improvements are welcome.

## Test Hello World
A simple hello world example:

  
  ```c++
  // foo.cpp
  #include "sut.h"
  
  DESCRIBE("World")
  {
      IT("should be fair to assume that the world still works",
      {
          S_ASSERT(1 == 1, "wat?");
      });
  }
  END()
  ```
## Limitations
As the DESCRIBE macro contains a main function, only one can be used per executable test. 
