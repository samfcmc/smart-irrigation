Smart Irrigation Arduino
===============================

Code that will run in Arduino using the following sketch:

# Requirements:
* An Arduino board (we used Arduino Uno R3)
* <a href="https://github.com/sudar/Arduino-Makefile">Arduino-mk</a> 
(will be really useful to make the building process much easier)
* <a href="https://github.com/ivanseidel/ArduinoThread">Arduino Threads</a> 
library

# Usage
* Create a Makefile from the existing template
```
cp Makefile-template Makefile
```
* Change the new Makefile according to what makes sense in your machine
* Compile the code:
```
make
```
* Connect your Arduino through a USB port and upload the code to it:
```
make upload
```
