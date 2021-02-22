#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;
vector<int> primes = {2};
vector<int> primepairs;

void calculate(int n)
{
    const int largest_prime = primes.back();
    if (largest_prime >= n)
    {
        return;
    }
    for(size_t i = largest_prime +1; i <= n; i++)
    {
        bool not_prime = false;
        for (size_t j = 0; j < primes.size(); j++)
        {
            if(i%primes[j] == 0)
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
bool check(int n)
{
    calculate(n);
    return std::find(primes.begin(), primes.end(), n) != primes.end();
}
int main(void)
{
    tuple<int, int> pair;
    int number = 10000;
    for (int i = 2; i<= number; i++)
    {
        calculate(i);
    }
    for (size_t i = 0; i < primes.size(); i++)
    {
        if(primes[i]+2 == primes[i+1])
        {
            primepairs.push_back(primes[i]);
            primepairs.push_back(primes[i+1]);
        }
    }
    for (size_t j = 0; j < primepairs.size(); j++)
    {
        if(j%2 == 0)
        {
            std::cout << endl;
        }
        std::cout << primepairs[j] << " ";
    }
    return 0;
}