
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

    int sendbuff[SIZE];
    int recvbuff[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        sendbuff[i] = 1;
    }
    start = MPI_Wtime();
    MPI_Reduce(&sendbuff[0], &recvbuff[0], SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    finish = MPI_Wtime();
    if (rank == 0)
    {
        cout << "The results for the first 5 elems" << endl;
        cout << recvbuff[0] << "," << recvbuff[1] << "," << recvbuff[2] << "," << recvbuff[3] << "," << recvbuff[4] << endl;
        double time_reduce = stop_reduce - start_reduce;
        cout << "Reduce time: " << time_reduce << endl;
    }
    MPI_Finalize();
    return 0;
}
