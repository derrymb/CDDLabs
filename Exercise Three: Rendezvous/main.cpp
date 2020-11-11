/*! \mainpage Lab 3 Rendezvous
    \author Derry Brennan 
    \date 30/10/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Rendezvous
    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
    Rendezvous are when two threads must complete a certain part each before both move on to the remaining work
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class Rendezvous
    \brief An Implementation of a Rendezvous using Semaphores

    Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
    Rendezvous are when two threads must complete a certain part each before both move on to the remaining work
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief This function will sleep and then make print screen the message "Task One has arrived! ", have a rendezvous point with taskTwo and then print "Task One has left!"
    \param firstSem The first semaphore used for flow control
    \param secondSem The second Semaphore used for flow control
    \param delay the int used for number of seconds for the thread to sleep

    both firstSem and secondSem haave the inital int value of 0 unless supplied with a alternate
    delay is assigned in main, used as an artifical delay to thread proceedings to test different interleavings
    The function prints out "Task One has arrived! " before the rendezvous point.
    And prints "Task One has left!" after the rendezvous point.
    There are a number of ways to handle the rendezvous, but here I signaled firstSem and told secondSem to wait
    and will do the oppisite in taskTwo (wait firstSem and signal secondSem, in that order!)  
*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Signal();
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
/*! \fn taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
    \brief This function will sleep and then make print screen the message "Task Two has arrived ", have a rendezvous point with taskOne and then print "Task Two has left "
    \param firstSem The first semaphore used for flow control
    \param secondSem The second Semaphore used for flow control
    \param delay the int used for number of seconds for the thread to sleep

    both firstSem and secondSem haave the inital int value of 0 unless supplied with a alternate
    delay is assigned in main, used as an artifical delay to thread proceedings to test different interleavings
    The function prints out "Task One has arrived! " before the rendezvous point.
    And prints "Task One has left!" after the rendezvous point.
    There are a number of ways to handle the rendezvous, but here I waited firstSem and told secondSem to signal
    and will do the oppisite in taskOne (signal firstSem and wait secondSem, in that order!)  
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  firstSem->Wait();
  secondSem->Signal();
  std::cout << "Task Two has left "<<std::endl;
}
/*! Mian function*/
/*! \fn void main(void)
    \brief main function of the program, creates and runs 2 threads
    In the main function we create 2 threads and a semaphore
*/

int main(void){
  /*! 
    \var thread threadOne, threadTwo
    \brief The 2 threads we will use to demonstrate the rendezvous 
  */
  std::thread threadOne, threadTwo;
  /*! 
    \var Semaphore sem1, sem2
    \brief the 2 semaphores needed to achieve a rendezvous between threads, each inialized to default 0
  */
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  /*! 
    \var int taskOneDelay, taskTwoDelay
    \brief variables used to signify how long the threads will sleep for 
  */
  int taskOneDelay=1;
  int taskTwoDelay=5;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
