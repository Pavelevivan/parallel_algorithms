#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    int n = atoi(argv[1]);
    
    int **mat_1 = new int *[n];
    int **mat_2 = new int *[n];
    for (int i=0; i<n; i++) {mat_1[i] = new int [n];}
    for (int i=0; i<n; i++) {mat_2[i] = new int [n];}

    clock_t start;
    clock_t finish;

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        mat_1[i][j] = rand() % 10;
        mat_2[i][j] = rand() % 10;
    }

    double time;
    double n_1_time;

    cout << "Order i-j-k" << endl;
    for (int numThreads = 1; numThreads <= 10; numThreads++) {

        int **mat_3 = new int *[n];
        for (int i=0; i<n; i++) {mat_3[i] = new int [n];}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    mat_3[i][j] = 0;
                    for (int k = 0; k < n; k++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        cout << "Threads = " << numThreads << "  ";
        n_1_time = double(finish - start) / CLOCKS_PER_SEC;
        cout << "Time = " << n_1_time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

   cout << "Order i-k-j" << endl;
   for (int numThreads = 1; numThreads <= 10; numThreads++) {

       int **mat_3 = new int *[n];
       for (int i=0; i<n; i++) {mat_3[i] = new int [n];}
       for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {mat_3[i][j] = 0;}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int i = 0; i < n; i++) {
                for (int k = 0; k < n; k++) {
                    for (int j = 0; j < n; j++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        time = double(finish - start) / CLOCKS_PER_SEC;

        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

   cout << "Order j-i-k" << endl;
   for (int numThreads = 1; numThreads <= 10; numThreads++) {

       int **mat_3 = new int *[n];
       for (int i=0; i<n; i++) {mat_3[i] = new int [n];}
       for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {mat_3[i][j] = 0;}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int j = 0; j < n; j++) {
                for (int i = 0; i < n; i++) {
                    for (int k = 0; k < n; k++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        time = double(finish - start) / CLOCKS_PER_SEC;

        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

   cout << "Order j-k-i" << endl;
   for (int numThreads = 1; numThreads <= 10; numThreads++) {

       int **mat_3 = new int *[n];
       for (int i=0; i<n; i++) {mat_3[i] = new int [n];}
       for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {mat_3[i][j] = 0;}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    for (int i = 0; i < n; i++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        time = double(finish - start) / CLOCKS_PER_SEC;

        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

   cout << "Order k-i-j" << endl;
   for (int numThreads = 1; numThreads <= 10; numThreads++) {

       int **mat_3 = new int *[n];
       for (int i=0; i<n; i++) {mat_3[i] = new int [n];}
       for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {mat_3[i][j] = 0;}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        time = double(finish - start) / CLOCKS_PER_SEC;

        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

   cout << "Order k-j-i" << endl;
   for (int numThreads = 1; numThreads <= 10; numThreads++) {

       int **mat_3 = new int *[n];
       for (int i=0; i<n; i++) {mat_3[i] = new int [n];}
       for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {mat_3[i][j] = 0;}

        start = clock();
        #pragma omp parallel for num_threads(numThreads)
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    for (int i = 0; i < n; i++) {
                        mat_3[i][j] = mat_3[i][j] + mat_1[i][k] * mat_2[k][j];
                    }
                }
            }
        finish = clock();

        if (numThreads==1) {n_1_time = double(finish - start) / CLOCKS_PER_SEC;}

        time = double(finish - start) / CLOCKS_PER_SEC;

        cout << "Threads = " << numThreads << "  ";
        cout << "Time = " << time << " ";
        cout << "Efficiency = " << n_1_time / time << endl;
   }

    return 0;
}