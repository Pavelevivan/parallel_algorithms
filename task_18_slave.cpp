#include "mpi.h"
int main(int argc, char **argv)
{
	int rank;
	MPI_Comm intercomm;
	MPI_Init(&argc, &argv);
	// Get parent communicator
	MPI_Comm_get_parent(&intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank < 2)
		// Send rank to parent
		MPI_Send(&rank, 1, MPI_INT, 0, rank, intercomm);
	else
	{
		//Send slaves number to parent
		int size;
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Send(&size, 1, MPI_INT, 0, rank, intercomm);
	}
	MPI_Finalize();
	return 0;
}