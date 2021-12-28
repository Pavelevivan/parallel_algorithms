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
    const int batch_size = SIZE / size;
    int vec_sum = 0;
    int vec_sum_loc = 0;

    for (int i = 0; i < SIZE; i++)
    {
        vec_base[i] = 1;
    }

    int strt = batch_size * rank;
    int end = batch_size * (rank + 1);
    if (rank == size - 1)
        end = SIZE;

    for (int i = strt; i < end; i++)
    {
        vec_sum_loc += vec_base[i];
    }

    start = MPI_Wtime();

    for (int range = 2; range <= size; range *= 2)
    {
        if ((rank / range) * range + range / 2 == rank)
        {
            MPI_Send(&vec_sum_loc, 1, MPI_INT, (rank / range) * range, range, MPI_COMM_WORLD);
        }
        else if (rank % range == 0)
        {
            MPI_Recv(&vec_sum, 1, MPI_INT, (rank / range) * range + range / 2, range, MPI_COMM_WORLD, &status);
            vec_sum_loc += vec_sum;
        }
    }

    finish = MPI_Wtime();

    if (rank == 0)
    {
        cout << "Total sum of array: " << vec_sum_loc << endl;
        cout << "Execution time for reduce method: " << finish - start << endl;
    }

    MPI_Finalize();
    return 0;
}