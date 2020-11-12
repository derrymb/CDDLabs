// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: Implementation of a barrier using semaphores
// Author: Derry Brennan
// Maintainer: Derry Brennan
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"

class Barrier
{
    private:
        std::shared_ptr<Semaphore> first( new Semaphore(0));
        std::shared_ptr<Semaphore> second( new Semaphore(1));
        std::shared_ptr<Semaphore> mutexSem (new Semaphore(1));
        std::condition_variable mCond;
        std::size_t mCount;
    public:
        explicit Barrier(std::size_t count) : mCount(count) { }
           
    void Wait()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (--mCount == 0)
        {
            mCond.notify_all();
        }
        else
        {
            mCond.wait(lock, [this] {return mCount ==0;})
        }
    }
};

// 
// Barrier.cpp ends here
