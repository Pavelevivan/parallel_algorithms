#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, n, i, message;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        int temp;
        int msg;
        for (i = 1; i < n; i++)
        {
            temp = rand() % 10 + 1;
            if (temp > n)
            {
                msg = temp - n + 1;
            }
            else
            {
                msg = temp;
            }

            MPI_Send(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if (message > rank)
        {
            cout << "Recieved value " << message << endl;
        }
    }
    MPI_Finalize();
    return 0;
}