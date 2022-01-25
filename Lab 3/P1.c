#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// When forking fails
void failFork()
{
	printf("ERROR: Fork failed.");
	exit(3);
}

// When piping fails
void failPipe()
{
	printf("ERROR: Pipe did not open as expected.");
	exit(2);
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Error: Input not provided.\n");
		return 1;
	}

	int a, b;
	sscanf(argv[1], "%d", &a);
	sscanf(argv[2], "%d", &b);

	int fd1[2]; // File Descriptor for comm with Child 1
	int fd2[2]; // File Descriptor for comm with Child 2

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
		failPipe();

	pid_t sumPID = fork();

	if (sumPID == -1)
		failFork();

	// If child1 process is running
	if (sumPID == 0)
	{
		int sum = a + b;
		printf("Sum of %d and %d (by Child1: %d): %d\n", a, b, getpid(), sum);
		write(fd1[1], &sum, sizeof(int));
	}
	else
	{
		pid_t prodPID = fork();
		if (prodPID == -1)
			failFork();
		// If child2 process is running
		if (prodPID == 0)
		{
			int product = a * b;
			printf("Product of %d and %d (by Child2: %d): %d\n", a, b, getpid(), product);
			write(fd2[1], &product, sizeof(int));
		}
		// If parent process is running
		else
		{
			int sum, product;
			read(fd1[0], &sum, sizeof(int));
			read(fd2[0], &product, sizeof(int));
			printf("Division of %d and %d (by Parent: %d): %f\n", product, sum, getpid(), (double)product / (double)sum);
		}
	}
	return 0;
}