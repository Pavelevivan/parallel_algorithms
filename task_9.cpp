#include <mpi.h>
#include <iostream>
using namespace std;

int const N_TEST = 1048576; // 2^20 or 4^10 -> 2 or 4 processes

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n;
    int *a;

    if (rank == 0)
    {
        if (argc == 1)
        {
            n = N_TEST;
        }
        else
        {
            n = atoi(argv[1]);
        }
        a = new int[n];
        fill(a, a + n, 1);
    }

    double start_time;
    if (rank == 0)
    {
        start_time = MPI_Wtime();
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = N_TEST; i > 4; i = i / 2)
    {
        int *sub_a = new int[i / size];
        int *sum_sub_a = new int[(i / size) / 2];

        MPI_Scatter(a, i / size, MPI_INT, sub_a, i / size, MPI_INT, 0, MPI_COMM_WORLD);

        for (int j = 0; j < (i / size) / 2; j++)
        {
            sum_sub_a[j] = sub_a[2 * j] + sub_a[(2 * j) + 1];
        }

        if (rank == 0)
        {
            delete[] a;
            a = new int[i / 2];
        }
        MPI_Gather(sum_sub_a, (i / size) / 2, MPI_INT, a, (i / size) / 2, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        double elapsed_time = MPI_Wtime() - start_time;
        cout << "Result of sum is " << a[0] + a[1] + a[2] + a[3] << endl
             << "Elapsed time of cascade model is " << elapsed_time;
        delete[] a;
    }

    int sum;
    if (rank == 0)
    {
        a = new int[n];
        fill(a, a + n, 1);
        start_time = MPI_Wtime();
        sum = 0;
    }
    int *sub_a = new int[n / size];
    int sub_sum = 0;

    MPI_Scatter(a, n / size, MPI_INT, sub_a, n / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n / size; i++)
    {
        sub_sum += sub_a[i];
    }

    MPI_Reduce(&sub_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        double elapsed_time = MPI_Wtime() - start_time;
        cout << endl
             << endl
             << "Reduce sum of array is " << sum << endl;
        cout << "Elapsed time is " << elapsed_time << endl;
    }

    MPI_Finalize();
    return 0;
}