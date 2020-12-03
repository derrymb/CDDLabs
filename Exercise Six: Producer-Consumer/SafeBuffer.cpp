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
#include "SafeBuffer.h"
#include <iostream>
#include <stdlib.h>
#include "Event.h"
/*! \page SafeBuffer
    \file SafeBuffer.cpp
    \author Derry Brennan 
    \date 27/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name SafeBuffer implementation

    The constructor and implementation of the SafeBuffer class
*/
/*! \class SafeBuffer
    \brief A safe buffer that implements a mutual exclusion on the access to it and has
    the waits and signals used by the semaphore to organise their flow

    A Buffer of Events created using a vector and has a mutex used for mutual exclusion 
    and a semaphore to control the flow between producers and consumers
*/
SafeBuffer::SafeBuffer()
{
    theMutex = std::make_shared<Semaphore>(1);
    theSemaphore = std::make_shared<Semaphore>(0);
}
/*!
    \fn SafeBuffer::push(Event newChar)
    \brief the push function used to insert an event into the buffer
    \param newChar An event object created which is a lower case character

    SafeBuffer push function. Engages an mutex lock, adds an event object onto the buffer, releases the mutex lock 
    and then signals the consumers to let wake one up ready to consume produced object
*/
int SafeBuffer::push(Event newChar)
{
    theMutex->Wait();
    theData.push_back(newChar);
    int size = theData.size();
    theMutex->Signal();
    theSemaphore->Signal();
    return size;
}
/*!
    \fn SafeBuffer::pop()
    \brief the pop function used to consume an event from the buffer

    SafeBuffer pop function. Has a wait() to make sure they do not proceed while nothing is nothing to consume
    Engages an mutex lock, takes the Event from the buffer and performs an operation of changing it to an uppercase character 
    then releases the mutex lock once its operations get complete
*/
Event SafeBuffer::pop()
{
    theSemaphore->Wait();
    theMutex->Wait();
    Event e = theData.back();
    theData.pop_back();
    theMutex->Signal();
    return e;
}
