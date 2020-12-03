/*! \mainpage Lab 5 Reusable Barriers
    \author Derry Brennan 
    \date 19/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Reusable Barriers

    Using C++ Semaphores to make a mutex and a turnstile to construct a reusable barrier
    to allow the rendezvous of N threads that will work inside a loop
*/
/*!
    \file Barrier.h
    \brief the definitions of the Barrier class 
    \var int numThreads  the number of threads the barrier will work with
    \var Semaphore first{0} the first semaphore used as a turnstile in conjunction with second. Initilased to 0
    \var Semaphore second{1} the second semaphore used as a turnstile in conjunction with first. Initilased to 1
    \var Semaphore mutexSem{1} the semaphore used as a mutex lock. Initilased to 1 to allow the first thread to pass through and not wait,
    but all others must wait until the thread in the critical section finishes and signals the next
    \var int barrierCount = 0 a counter used to determine the last thread through each phase

    Constructor, Destructor, phaseOne(), phaseTwo(), and Wait() functions of the Barrier class
*/
#pragma once
#include "Semaphore.h"


class Barrier{
  int numThreads;
  Semaphore first{0};
  Semaphore second{1};
  Semaphore mutexSem{1};
  int barrierCount = 0;
  public:
    Barrier(int totalThreads):numThreads(totalThreads){};
    virtual ~Barrier();
    void wait();
    void phaseOne();
    void phaseTwo();
};

