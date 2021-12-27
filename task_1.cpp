#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <omp.h>
#include <cstdlib>

using namespace std;

const int a = 0;    //Left border of random values range
const int b = 1000; //Right border of random values range

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int n = atoi(argv[1]);
    int *v = new int[n];

    for (int i = 0; i < n; i++)
    {
        v[i] = rand() % (b - a + 1) + a;
    }

    for (int numThreads = 1; numThreads <= 10; numThreads++)
    {

        int max_val = a;

        clock_t start = clock();

#pragma omp parallel for num_threads(numThreads) reduction(max \
                                                           : max_val)
        for (int i = 0; i < n; i++)
        {
            if (v[i] > max_val)
                max_val = v[i];
        }

        clock_t finish = clock();

        cout << "Max value = " << max_val << " ";
        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << double(finish - start) / CLOCKS_PER_SEC << endl;
    }

    delete[] v;

    return 0;
}