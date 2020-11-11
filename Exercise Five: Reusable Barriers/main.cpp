#include "Barrier.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
 

static const int num_threads = 100;
int sharedVariable=0;
int barrierCount;


void barrierTask(std::shared_ptr<Semaphore> mutex, std::shared_ptr<Semaphore> first, std::shared_ptr<Semaphore> second, int numThread)
{
  //Do first bit of task
  for (int i = 0; i < 2; i++)
  {
    //rendezvous
    std::cout << numThread << " ";
    mutex->Wait();
    barrierCount++;
    if (barrierCount == num_threads)
    {
      std::cout << std::endl;
      second->Wait();
      first->Signal();
    }
    mutex->Signal();
    first->Wait();
    first->Signal();
    // critical point
    mutex->Wait();
    --barrierCount;
    if (barrierCount == 0)
    {
      first->Wait();
      second->Signal();
    }
    //Do second half of task
    std::cout<< "B";
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