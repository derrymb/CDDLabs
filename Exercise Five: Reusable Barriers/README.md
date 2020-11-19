# License:        
This code is covered by the GNU General Public License v3.0
# Author:         
Derry Brennan
# Install:
```        
make
./barrier
```
# Dependencies:   
```
g++
make
```
# TODO:           
figure out how to use \var in doxygen and just how to comment properly
# Files:          
*main.cpp contains the threads that we want to order the flow of control of
*Semaphore.cpp contains the class semaphore and its functions
*Semaphore.h contains the c++ header for the implementation of semaphores
*barrier.cpp contains the barrier class upon implementation
*barrier.h c++ header file for the barrier class

# Info:           
this lab was to get us to understand how to use semaphores to order the flow of threads \
using semaphore.Wait() and semaphore.Signal() to order the threads how we want then to run
