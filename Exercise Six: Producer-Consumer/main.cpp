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
/*! \mainpage Lab 5 Producer Consumer Threads
    \file main.cpp
    \author Derry Brennan 
    \date 27/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Producer Consumer

    Using C++ semaphores and vectors of threads implement a showcase for the producer consumer problem.
    This requires the buffer to handle the mutual exclusion of its shared resource between the producer and consumer
    Also the producer must signal to let consumers know something has been produced and is now ready to be consumed
*/
/*!
    \file Barrier.cpp
    \brief the functions of the Barrier class

    Destructor, phaseOne(), phaseTwo(), and Wait() functions of the Barrier class
*/
#include "Event.h"
#include <iostream>
#include <thread>
#include <vector>
#include "SafeBuffer.h"

static const int num_threads = 100; //!< The number of threads to be made for both producer and consumer

/*! \fn void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
    \brief Creates events and adds them to buffer
    \param theBuffer
    \param numLoops

    Produce event and add to buffer
*/
void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{
  for(int i=0;i<numLoops;++i){
    Event event ;
    theBuffer->push(event);
  }
}

/*! \fn void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
    \brief Takes events from buffer and consumes them
    \param theBuffer
    \param numLoops

    Produce event and add to buffer
*/
void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops)
{
  for(int i=0;i<numLoops;++i){
    Event event;//!< The created event that will be stored on the buffer
    event = theBuffer->pop();
    event.consume();
  }
}

int main(void){

  std::vector<std::thread> producers(num_threads);//!< The vector of threads used as consumers
  std::vector<std::thread> consumers(num_threads);//!< The vector of threads used as producers
  std::shared_ptr<SafeBuffer> buffer( new SafeBuffer());//!< The safeBuffer used to store the Events
  /**< Launch the threads  */
  for(std::thread& prod: producers)
  {
    prod=std::thread(producer,buffer,10);
  }
  for(std::thread& cons: consumers)
  {
    cons=std::thread(consumer,buffer,10);
  }
  /**< Join the threads with the main thread */
  for (auto& p :producers)
  {
      p.join();
  }
  for (auto& c :consumers)
  {
      c.join();
  }
  std::cout << std::endl;
  return 0;
}
