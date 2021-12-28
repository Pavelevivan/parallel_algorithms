#include <stdio.h>
#include <algorithm>
#include "mpi.h"

#define SIZE 1000000

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    double start, finish;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vec_base[SIZE];
    int vec_sum_loc = 0;
    int vec_sum = 0;
    int vec_summed_sum = 0;

    for (int i = 0; i < SIZE; i++)
    {
        vec_base[i] = 1;
    }

    // divide vector into batches
    const int batch_size = SIZE / size;

    int strt = batch_size * rank;
    int end = batch_size * (rank + 1);
    if (rank == size - 1)
        end = SIZE;

    for (int i = strt; i < end; i++)
    {
        vec_sum_loc += vec_base[i];
    }

    start = MPI_Wtime();
    MPI_Reduce(&vec_sum_loc, &vec_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    finish = MPI_Wtime();

    if (rank == 0)
    {
        cout << "Total sum of array: " << vec_sum << endl;
        cout << "Execution time for reduce method: " << finish - start << " seconds" << endl;
    }

    MPI_Finalize();
    return 0;
}