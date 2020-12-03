/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Event.h"
#include <iostream>
#include <stdlib.h>
/*! \page Event
    \file Event.cpp
    \author Derry Brennan 
    \date 27/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Event implementation

    The constructor and implementation of the Event class, the constructor selects an random character from a-z as the "Event"
*/
/*! \class Event
    \brief An Implementation of a Reusable Barriers using Semaphores

    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/
//Output a random alphabetic character in lower case
//the produced variable
Event::Event(){
  theChar = 'a'+rand()%26;
  std::cout << theChar;
}

//output a particular character in upper case
//the consumed variable
void Event::consume(){
    char upperChar = theChar-32;    
    std::cout << upperChar;
}