#include <omp.h>
#include <iostream>
int main(void)
{
    int omp_get_thread_num();
    {
        int count = 0;
        #pragma omp parallel for schedule(dynamic) num_threads(2048)
        for(int i = 0; i < 1000000; i++)
        {
            if(count = 0)
            {
                printf("Thread rank entered the for loop: %d\n", omp_get_thread_num());
            }
            count++;
        }
         
    }
    return 0;
}