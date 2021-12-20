#include <iostream>
#include <mpi.h>
#define sz 1000000
int arr1[sz];
int arr2[sz];
void fillVectors(int n)
{
    for (int i = 0; i < n; i++)
    {
        arr1[i] = 1;
        arr2[i] = 1;
    }
}
int main(int argc, char *argv[])
{
    int start, stop;
    int sBufer = 0;
    MPI_Init(&argc, &argv);
    int rank, n, i, message;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        int rBufer;
        fillVectors(sz);
        start = 0;
        stop = start + sz / n + sz % n;
        for (int i = 1; i < n; i++)
        {
            start = stop;
            stop = std::min(start + sz / n, sz);
            MPI_Send(&arr1[start], stop - start, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&arr2[start], stop - start, MPI_INT, i, 2, MPI_COMM_WORLD);
        }
        start = 0;
        stop = start + sz / n + sz % n;
        for (int i = start; i < stop; i++)
            sBufer += arr1[i] * arr2[i];
        for (int i = 1; i < n; i++)
        {
            MPI_Recv(&rBufer, sz / n, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
            sBufer += rBufer;
        }
        std::cout << "Result: " << sBufer << std::endl;
    }
    else
    {
        MPI_Recv(&arr1, sz / n, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&arr2, sz / n, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        for (int i = 0; i < sz / n; i++)
            sBufer += arr1[i] * arr2[i];
        MPI_Send(&sBufer, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}