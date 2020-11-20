/*! \mainpage Lab 5 Reusable Barriers
    \author Derry Brennan 
    \date 19/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Reusable Barriers

    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/
/*! \class Barrier
    \brief An Implementation of a Reusable Barriers using Semaphores

    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/
/*!
    \file Barrier.cpp
    \brief the functions of the Barrier class

    Destructor, phaseOne(), phaseTwo(), and Wait() functions of the Barrier class
*/
// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>

/*!
    \fn Barrier::~Barrier()
    \brief destructor function of barrier

    Barrier destructor
*/
Barrier::~Barrier()
{
    //Nothing to do here
}
/*!
    \fn void Barrier::phaseOne()
    \brief The first phase of the rendezvous between n threads

    Using semaphores and mutex lock order the flow of all threads to wait at the end for the last thread to be ready before moving on
*/
void Barrier::phaseOne()
{
    mutexSem.Wait();
    ++barrierCount;
    if (barrierCount == numThreads)
    {
      std::cout << std::endl;
      second.Wait();   // close 2nd door
      first.Signal();  // open 1st door
    }
    mutexSem.Signal();
    first.Wait();
    first.Signal();
}
/*!
    \fn void Barrier::phaseTwo()
    \brief The second phase of the rendezvous between n threads

    sing semaphores and mutex lock order the flow of all threads to wait at the end for the last thread to be ready before moving on
*/
void Barrier::phaseTwo()
{
    mutexSem.Wait();
    --barrierCount;
    if (barrierCount == 0)
    {
      first.Wait();    //close first door
      second.Signal(); // open 2nd door
    }
    if (barrierCount == 0)
    {
      std::cout<< std::endl;
    }
    mutexSem.Signal();
    second.Wait();
    second.Signal();
}
/*!
    \fn void Barrier::wait()
    \brief The wait function runs phaseOne() and phaseTwo() sequentially 

*/
void Barrier::wait()
{
    phaseOne();
    phaseTwo();
}
// Barrier.cpp ends here
