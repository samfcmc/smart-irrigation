Smart Irrigation Arduino
===============================

Code that will run in Arduino using the following sketch:

<img src="https://raw.githubusercontent.com/samfcmc/smart-irrigation/master/docs/img/simulation.png?token=AErVfhvSjhIIFm7Ma5yK7a2TGOjTcqfpks5Ukh4pwA%3D%3D"/>

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
