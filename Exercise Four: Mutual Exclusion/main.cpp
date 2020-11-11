/*! \mainpage Lab 4 Mutual Exclusion
    \author Derry Brennan 
    \date 6/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Mutual Exclusion
    Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
    Example of how to achieve mutual exclusion achieved with a semaphore
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

/*! 
    \var int num_threads
    \brief the number of threads we will create to do our work for us 
  */
static const int num_threads = 100;
/*! 
    \var int sharedVariable
    \brief the shared variable that all our threads will try to increment 
  */
int sharedVariable=0;


/*! \fn void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief An Implementation of Mutual Exclusion using Semaphores
    \param firstsem Semaphore used to achieve mutual exclusion. it is initalized to 1 to allow to first wait() call to continue
    \param numUpdates
    Uses C++11 features such as mutex and condition variables to implement an example of mutual exclusion for threads
    The function will have a \var int num_threads of threads attempt to increment a single shared variable \var int sharedVariable
    We have established a mutex lock arouns sharedVariable in order to only allow one thread at a time to have access to this variable
*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
{
  for(int i=0;i<numUpdates;i++)
  {
    firstSem->Wait();
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
    firstSem->Signal();
  }
}

/*! Mian function*/
/*! \fn void main(void)
    \brief main function of the program, creates and runs 2 threads
    In the main function we create 2 threads and a semaphore
*/
int main(void){
  /*! 
    \var vector<thread> vt 
    \brief a vector holding all the threads we created, think thread pool 
  */
  std::vector<std::thread> vt(num_threads);
  /*! 
    \var Semaphore aSemaphore
    \brief the semaphore we will use to achieve mutual exclusion, initalized to 1 
  */
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  /*!
    for loop going through all the threads in vector vt and calling update task with each
  */
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
