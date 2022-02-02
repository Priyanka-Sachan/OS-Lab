#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    sscanf(argv[1], "%d", &n);
    while (n--)
    {
        pid_t PID = fork();
        // Fork Failed
        if (PID < 0)
            printf("ERROR: Fork failed.\n");
        // Parent Process
        else if (PID > 0)
            printf("Orphan process %d created.\n", PID);
        // Child Process
        else
        {
            sleep(50);
            exit(0);
        }
    }
    return 0;
}