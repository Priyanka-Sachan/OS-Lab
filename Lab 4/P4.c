#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    pid_t PID;

    PID = fork();
    // Child : Copy source program to another file f2
    if (PID == 0)
    {
        FILE *fptr1 = fopen("P4.c", "r");
        FILE *fptr2 = fopen(filename, "w");
        char c = fgetc(fptr1);
        while (c != EOF)
        {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
        fclose(fptr1);
        fclose(fptr2);
        exit(0);
    }

    // Waits for child processes to terminate
    while (wait(NULL) > 0)
        ;
    PID = fork();
    // Child : Print contents of f2
    if (PID == 0)
    {
        FILE *fptr = fopen(filename, "r");
        char c = fgetc(fptr);
        while (c != EOF)
        {
            putc(c, stdout);
            c = fgetc(fptr);
        }
        fclose(fptr);
        exit(0);
    }

    // Waits for child processes to terminate
    while (wait(NULL) > 0)
        ;
    PID = fork();
    // Child : Delete file f2
    if (PID == 0)
    {
        remove(filename);
        exit(0);
    }
    return 0;
}