#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void generateLucasSequence(int n, int *seq)
{
    seq[0] = 2;
    seq[1] = 1;
    for (int i = 2; i < n; i++)
        seq[i] = seq[i - 1] + seq[i - 2];
}
void printLucasSequence(int n, int seq[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", seq[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n;
    sscanf(argv[1], "%d", &n);

    int luSeq[n];
    for (int i = 0; i < n; i++)
        luSeq[i] = 0;

    // File descriptor for piping
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Piping failed.");
        exit(3);
    }

    pid_t PID = fork();
    // Child : Generate Lucas sequence
    if (PID == 0)
    {
        generateLucasSequence(n, luSeq);
        write(fd[1], luSeq, sizeof(int) * n);
    }
    // Parent process
    else
    {
        // Waits for child process to terminate
        while (wait(NULL) > 0)
            ;
        PID = fork();
        // Child : Print Lucas sequence
        if (PID == 0)
        {
            read(fd[0], luSeq, sizeof(int) * n);
            printLucasSequence(n, luSeq);
        }
    }
    return 0;
}