/*! \mainpage Lab 5 Barriers
    \author Derry Brennan 
    \date 19/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Reusable Barriers

    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
    Example of how to achieve mutual exclusion achieved with a semaphore
*/
#include "Barrier.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 10;
int barrierCount;

/*! \fn void barrierTask1(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numThread)
    \brief This function will have a given number of threads (num_threads) enter and all threads will print out their number and wait until all have arrived 
    before each print out a "B" and then loop around and do it again
    \param mutex a mutex lock used to restrict access to critical section of code
    \param first the first of 2 Semaphores used in conjunction to form a turnstile effect on the threads, initialized to 0
    \param second the second of 2 Semaphores used in conjunction to form a turnstile effect on the threads, initialized to 1
    \param numThread the unique number assigned to each thread, from 1 to num_threads, used to print to screen

    Each thread enters and prints out its unique number to the screen
    then using a mutex lock each thread in turn will increment the global 
    variable barrier count and check to see if they are the last thread to this section (if (barrierCount == num_threads))
    all other threads but the last thread will wait at the first "first->Wait()" until the last thread meets the if statments condition (if (barrierCount == num_threads)).
    The last thread will then signal first and each thread will wake the previous
    Then we repeat the same steps to see tha last thread to get to the second section with the conditional  if (barrierCount == 0)
    the last thread in here will wake up a sleeping thread and everyone will move on again to the next loop

*/
void barrierTask1(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numThread)
{
  //Do first bit of task
  for (int i = 0; i < 5; i++)
  {
    std::cout << numThread << " ";
    mutex->Wait();
    barrierCount++;
    if (barrierCount == num_threads)
    {
      std::cout << std::endl;
      second->Wait();   // close 2nd door
      first->Signal();  // open 1st door
    }
    mutex->Signal();
    first->Wait();
    first->Signal();
    mutex->Wait();
    --barrierCount;
    if (barrierCount == 0)
    {
      first->Wait();    //close first door
      second->Signal(); // open 2nd door
    }
    //Do second half of task
    std::cout << "B";
    if (barrierCount == 0)
    {
      std::cout<< std::endl;
    }
    mutex->Signal();
    second->Wait();
    second->Signal();
  }
}

/*! \fn void barrierTask2(std::shared_ptr<Barrier> theBarrier, int numLoops)
    \brief This function will have a given number of threads (num_threads) enter and all threads will print out their number and wait until all have arrived 
    before each print out a "B" and then loop around and do it again
    \param theBarrier a reusable barrier to organise a rendezvous between n threads
    \param numLoops the number of loops to be performed within this function

    The loop starts and each thread will perform the first task and wait at the first barrier->phaseOne() call until all threads have done the first part
    THey will then proceede to to the second part waiting at the second barrier->phaseTwo() for all threads to complete, before any threads move on to a new loop
*/
void barrierTask2(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << "A";
    //Barrier
    theBarrier->phaseOne();
    //Do second half of task
    std::cout<< "B";
    //Barrier
    theBarrier->phaseTwo();
  }
}

/*! \fn void barrierTask3(std::shared_ptr<Barrier> theBarrier, int numLoops)
    \brief This function will have a given number of threads (num_threads) enter and all threads will print out their number and wait until all have arrived 
    before each print out a "B" and then loop around and do it again
    \param theBarrier a reusable barrier to organise a rendezvous between n threads
    \param numLoops the number of loops to be performed within this function

    The loop starts and each thread will perform the first task and wait at the first barrier->wait() call 
    until all threads have done the first part before looping back
*/
void barrierTask3(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << i;
    //Barrier
    theBarrier->wait();
  }
  
}

/*! \fn int main(void)
    \brief The ever famous main function that runs our driver to show off barriers 
    
    We create a vector of threads, size determined by the global variable num_threads
    Instansiate Semaphores to use in the barrierless function barrierTask1()
    Instansiate a Barrier to be used in the barrier function barrierTask2(), it takes the num_threads as an arguement
    Instansiate a int i to be used as a counter for our threads in barrierTask1() and
    a int barrierCount to keep track of our threads in barrierTask1() also
    First loop runs the barrierTask1() with the provided semaphores and int i on all the threads
    in our vector of threads and joins threads together once it finishes
    Second loop uses the same vector of threads to run barrierTask2() that takes the aBarrier as its Barrier and 
    an integer for how many times the function will loop and joins the threads together once finished
*/
int main(void)
{
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> mutexSem( new Semaphore(1));
  std::shared_ptr<Semaphore> standardSem( new Semaphore(0));
  std::shared_ptr<Semaphore> standardSem1( new Semaphore(1));
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  int i=0;
  barrierCount =0;
  for(std::thread& t: vt)
  {
    t=std::thread(barrierTask1, mutexSem, standardSem, standardSem1, ++i);
  }
  for(auto& v :vt)
  {
    v.join();
  }
  for(std::thread& t: vt)
  {
    t=std::thread(barrierTask2, aBarrier, 5);
  }
  for(auto& v :vt)
  {
    v.join();
  }
  for(std::thread& t: vt)
  {
    t=std::thread(barrierTask3, aBarrier, 5);
  }
  for(auto& v :vt)
  {
    v.join();
  }
  return 0;
}