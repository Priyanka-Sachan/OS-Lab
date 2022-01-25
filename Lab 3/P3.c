#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Arguments : task1_script_name N n1 n2 n3 ... nN S task2_script_name n
int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("Error: Input not provided.\n");
        return 1;
    }
    pid_t PID = fork();
    // Child : Task1
    if (PID == 0)
    {
        // Separating arguements for task1
        char *argv_t1[argc - 2];
        argv_t1[0] = argv[1];
        for (int i = 1; i < argc - 3; i++)
            argv_t1[i] = argv[i + 1];
        argv_t1[argc - 3] = NULL;
        char *script_t1 = argv[1];
        execv(script_t1, argv_t1);
        printf("ERROR: execv() did not execute properly.");
    }
    // Parent : Task2
    else
    {
        // Separating arguements for task2
        char *argv_t2[3];
        argv_t2[0] = argv[argc - 2];
        argv_t2[1] = argv[argc - 1];
        argv_t2[2] = NULL;
        char *script_t2 = argv[argc - 2];
        execv(script_t2, argv_t2);
        printf("ERROR: execv() did not execute properly.");
    }
    return 0;
}