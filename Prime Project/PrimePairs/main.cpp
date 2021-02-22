/**
 * @file main.cpp
 * @class main
 * @author Liliana O'Sullivan
 * @brief An implementation of the Sieve of Eratosthenes.
 * @version 0.1
 * @date 12th February 2021
 * @copyright MIT License
 * 
 */

#include <iostream>
#include <chrono>
#include <omp.h>
#include <math.h>
using namespace std;

// 10 m - 4 s
// 100m 
// clang++ -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp main.cpp -std=c++11 -o main

/**
 * @brief A sequencial implementation of the Sieve. Uses a stack based sieve. This segment-faults at a high value of N
 * 
 * @param n The value to calculate primes up to.
 * @return long Amount of twin primes found up to N.
 */
long basic_sequential(long long n)
{
    bool a[n];

    for (long long i = 0L; i < n; ++i)
        a[i] = true;

    for (long long i = 2; i * i <= n; ++i)
        if (a[i])
            for (long long j = i * i; j <= n; j += i)
                a[j] = false;

    long count = 0L;
    for (long long i = 3; i < n - 2; i+=2)
    {
        if (a[i] and a[i + 2])
        {
            cout << "(" << i << "," << i + 2 << ")" << endl;
            count++;
        }
    }
    cout << "\t\t" << count << endl;
    return count;
}

/**
 * @brief A sequencial implementation of the Sieve. Uses a heap based sieve.
 * 
 * @param n The value to calculate primes up to.
 * @return long Amount of twin primes found up to N.
 */
long heap_basic_sequential(long long n)
{
    bool *a = new bool[n];
    //memset(a, true, sizeof(a)); 
    for (long long i = 0L; i < n; ++i)
       a[i] = true;

    for (long long i = 2; i * i <= n; ++i)
        if (a[i])
            for (long long j = i * 2; j <= n; j += i)
                a[j] = false;

    // long count = 0L;
    // for (long long i = 3; i < n - 2; i+=2)
    // {
    //     if (a[i] and a[i + 2])
    //         count++;
    // }
    // cout << "\t\t" << count << endl;
    delete[] a;
    //return count;
    return 0;
}

/**
 * @brief A concurrent implementation of the Sieve. Uses a heap based sieve.
 * 
 * @param n The value to calculate primes up to.
 * @return long Amount of twin primes found up to N.
 */
long concurrent(long long n) 
{
    bool *a = new bool[n];

    //omp_set_num_threads(500);
    #pragma omp parallel for
    for (int i = 0; i < n; ++i)
        a[i] = true;

    const unsigned long n_sqrt = sqrt(n);

    #pragma omp parallel for schedule(dynamic) // Static decreased performance over half
    for (long long i = 2; i <= n_sqrt; ++i)
        if (a[i])
            for (long long j = i * 2; j <= n; j += i)
                a[j] = false;

    // unsigned long count = 0L;
    // #pragma omp parallel for schedule(static)
    // for (long long i = 3; i < n - 2; i+=2)
    // {
    //     if (a[i] and a[i+2])
    //     {
    //         #pragma omp critical
    //         count++;
    //     }
    // }
    delete[] a;
    //cout << "\t\t" << count << endl;
    return 0;
}


/**
 * @brief A timer helper function to time the execution of one of the sieve functions.
 * 
 * @param f The function to be timed.
 * @param n The value passed to the sieve function. This is the amount to check primes up to.
 */
void time(long(*f)(long long),long long n)
{
    auto start = chrono::high_resolution_clock::now(); 
    (*f)(n);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << "Time taken: " << fixed << time_taken << " seconds" << endl;
}

int main()
{
    long long n = 100000000L;
    //concurrent(n);
    //time(heap_basic_sequential,n);
    heap_basic_sequential(n);
    return 0;
}