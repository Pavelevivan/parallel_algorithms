#include "mpi.h"
#include <cstring>
#include <stdio.h>
#define BUFSIZE 100

void createAndWriteToFile(const char *filename, const char *content, int content_length) {
	MPI_File fh;
	MPI_Status status;
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_write(fh, content, content_length, MPI_CHAR, &status);
	MPI_File_close(&fh);
}

int main(int argc, char **argv) {
	int bufsize, num, sum;
	// Initialize the MPI environment
	MPI_Init(&argc, &argv);
	// Create and write content to file
	createAndWriteToFile("file.txt", "Hello world!", 13);
	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	// Open file
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		//Read file data
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//Check the symbols number
	printf("Chars received %d\n", sum);

	//Delete file if needed;
	if (argc > 1 && strcmp(argv[1], "delete") == 0)
		MPI_File_delete("file.txt", MPI_INFO_NULL);

	MPI_Finalize();
}