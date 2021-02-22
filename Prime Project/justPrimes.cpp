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