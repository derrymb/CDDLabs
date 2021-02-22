#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;
vector<int> primes = {2};
vector<int> primepairs;

void calculate(int n)
{
    for(int i = 3; i <= n; i++)
    {
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
            primes.push_back(i);
        }
    }
}
int main(void)
{
    int number = 1000000;
    auto startTime = std::chrono::high_resolution_clock::now();
    calculate(number);
    sort(primes.begin(), primes.end());
    for (int i = 0; i < primes.size() -1; i++)
    {
        if(primes[i]+2 == primes[i+1])
        {
            {
                primepairs.push_back(primes[i]);
                primepairs.push_back(primes[i+1]);
            }
        }
    }
    sort(primepairs.begin(), primepairs.end());
    for (int j = 0; j < primepairs.size(); j++)
    {
        if(j%2 == 0 && j != 0)
        {
            std::cout << endl;
        }
        std::cout << primepairs[j] << " ";
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::cout << std::endl;
    std::cout << "Sequential execution for " << number << " numbers was : " << duration << " seconds.";
    return 0;
}