#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>

#define n 1000
using namespace std;

void MAXIMUM(void *x, void *y, int *size, MPI_Datatype *type)
{
	for (int i = 0; i < *size; i++)
	{
		((int*)y)[i] = max(((int*)x)[i], ((int*)y)[i]);
	}
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int a[n];
	int b[n];
	int copy[n];//extra

	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (i = 0; i < n; i++)
	{
		a[i] = i + rank + 1;
	}
	printf("Process %d a[0] = %d\n", rank, a[0]);

	MPI_Op_create((MPI_User_function*)&MAXIMUM, 1, &op);
	MPI_Reduce(a, b, n, MPI_INT, op, 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);

	MPI_Reduce(a, copy, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		cout <<"Maximum Value: " << b[0] << endl;
	}

	MPI_Finalize();
}