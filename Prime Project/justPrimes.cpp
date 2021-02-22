/*! \mainpage Prime Pairs Concurrency
    \author Derry Brennan 
    \date 11/02/2021
    \copyright This code is covered by the GNU General Public License v3.0
    \name Prime Pairs

    Using C++ and OpenMP to have a program calculate the prime numbers up until N and then find the prime pairs out of those
    Prime numbers, a prime pair is two prime numbers that are exactly 2 different from each other, e.g 3&5 or 5&7
    The calculations will be preformed concurrently using openmp to spin up threads and preak the computations up into chunks
    of the appropriate size for the number of threads. The program is timed to check the scalability of it as both the amount
    of numbers being calculated and the amount of threads preforming these calculations increase
*/
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
vector<int> primes = {2};

int main(void)
{
    int number = 100;
    int largest_prime = primes.back();
     
    #pragma omp parallel for shared(primes)
    for(int i = 3; i <= number; i++)
    {
        // #pragma omp critical
        // {
        //     std::cout << primes.size() << endl;
        // }
        bool not_prime = false;
        for (int j = 2; j < i; j++)
        {
            if(i%j == 0)
            {
                not_prime = true;
                break;
            }
        }
        if (!not_prime)
        {
            #pragma omp critical
            primes.push_back(i);
        }
    }
    for (size_t i = 0; i < primes.size(); i++)
    {
        cout << primes[i] << endl;
    }
    // sort(primes.begin(), primes.end());
    // for (int j = 0; j < primes.size(); j++)
    // {
    //     std::cout << primes[j] << endl;
    // }
}