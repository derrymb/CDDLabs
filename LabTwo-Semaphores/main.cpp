/*! \mainpage Lab 2 Semaphores
    \author Derry Brennan 
    \date 27/10/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Semaphores
   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 

*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class Signal
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 

*/
/*! displays a message first*/
/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief This function will sleep and then make print screen the message "I must print first"
    \param theSemaphore The semaphore used for flow control
    \param delay the int used for number of seconds for the thread to sleep

    theSemphore has the inital int value of 0 unless supplied with a alternate
    delay is assigned in main
    The function prints out "I must print first".
*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
  //tell task 2 to start now
}
/*! displays a message second*/
/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will print screen the message "This will appear second"
    \param theSemaphore The semaphore used for flow control

    theSemphore has the inital int value of 0 unless supplied with a alternate
    this function does not take a delay parameter
    The function prints out "This will appear second".
*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  //wait here until task one finishes....
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*! Mian function*/
/*! \fn void main(void)
    \brief main function of the program, creates and runs 2 threads
    In the main function we create 2 threads and a semaphore
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore());
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
