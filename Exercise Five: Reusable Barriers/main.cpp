/*! \mainpage Lab 5 Reusable Barriers
    \author Derry Brennan 
    \date 8/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Reusable Barriers
    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/
#include "Barrier.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
/*! \class Reusable Barriers
    \brief An Implementation of a Reusable Barriers using Semaphores

    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/

static const int num_threads = 100;
int sharedVariable=0;
int barrierCount;

/*! \fn void barrierTask(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numThread)
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
void barrierTask(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numThread)
{
  //Do first bit of task
  for (int i = 0; i < 2; i++)
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

/*! \fn barrierTask
    \brief An example of using a reusable barrier
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
/*
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task
    std::cout << "A"<< i;
    //Barrier
    theBarrier.wait();
    //Do second half of task
    std::cout<< "B" << i;
  }
  

}

int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  /*
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  /*
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
*/
int main(void)
{
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> mutexSem( new Semaphore(1));
  std::shared_ptr<Semaphore> standardSem( new Semaphore(0));
  std::shared_ptr<Semaphore> standardSem1( new Semaphore(1));
  int i=0;
  barrierCount =0;
  for(std::thread& t: vt)
  {
    t=std::thread(barrierTask, mutexSem, standardSem, standardSem1, ++i);
  }
  for(auto& v :vt)
  {
    v.join();
  }
  std::cout << std::endl << sharedVariable << std::endl;
  return 0;
}