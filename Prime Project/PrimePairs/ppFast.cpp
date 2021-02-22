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
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <omp.h>

bool checkPrime(int number)
{
    int num = number;
    if(num <= 1) return false;
    if(num <= 3) return true;

    if(num % 2 == 0 || num %3 ==0) return false;
    for(int i=5; i*i<=num; i=i+6)
    {
        if(num%i == 0 || num%(i+2) == 0)
        return false;
    }
    return true;
}
void primeRange(int first, int last)
{
    int i;
    int count = 0;
    #pragma omp parallel for num_threads(2)
    for(i = first; i<= last; i++)
    {
        if(checkPrime(i))
        {
            #pragma omp critical
            count ++;
        }
    }
    printf("The number of primes: %d \n", count);
}
void primePairs(int first, int last)
{
    int count = 0;
    #pragma omp parallel for num_threads(2)
    for(int i= first; i<= last; i++)
    {
        if(checkPrime(i) && checkPrime(i+2))
        {
            #pragma omp critical 
            count++;
            //printf("[ %d, %d ] \n", i, i+2);
        }
    }
    printf("There are %d prime pairs between %d and %d \n", count, first, last);
}
 
int main(int argc, char *argv[])
{
    int first=1;
    char *value = argv[1];
    int last = atoi(value);
    primeRange(first, last);
    primePairs(first, last);
    return 0;
}
