int * prime(int number)
{
    bool prime[number + 1];
    memset(prime, true, sizeof(prime));
    int count = number;
    for(int i = 2; i*i <= number; i++)
    {
        if(prime[i] == true)
        {
            for (int k = i*i; i <= number; k += i)
            {
                prime[i] = false;
                count--;
            }
        }
    }
    int primes[count];
    count = 0;
    for (int l = 2; l <= number; l++)
    {
        if(prime[l])
        {
            primes[count] = l;
            count++;
        }
    }
    return primes;
}