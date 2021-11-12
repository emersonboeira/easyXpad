# easyXpad
An easy and organized plug and play C++ library to abstract, read and deal with Xbox controllers signals and to practice my C++ skills and newby knowledge :D.

# Installation
To use easyXpad as a shared library on Linux it's necessary to compile the library's file using _make_ and then copy the header eXpad.h to /usr/local/include and the libeXpad.so to /usr/local/lib
```bash
# to compile the library - on easyXpad directory folder:
make

# on easyXpad directory folder:
sudo cp include/eXpad.h /usr/local/include/
sudo cp lib/libeXpad.so /usr/local/lib/
```
# Usage
To use easyXpad functions and classes, include the following header in your C++ code
```C
#include <eXpad.h>
```
And add the -leXpad flag to the g++ compiler linker!
