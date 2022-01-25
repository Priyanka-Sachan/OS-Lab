#include <stdio.h>

// Function to get xor of given two numbers
void xor (int a, int b)
{
    printf("XOR of %d and %d is: ", a, b);
    int axb = 0, pw = 1;
    // Iterating through numbers bit by bit
    while (a != 0 || b != 0)
    {
        int xr = (a % 2) * !(b % 2) + !(a % 2) * (b % 2);
        axb += xr * pw;

        a /= 2;
        b /= 2;
        pw *= 2;
    }
    printf("%d\n", axb);
}

int main(int argc, char *argv[])
{
    // Check argument count
    if (argc < 3)
        printf("Error: Input not available.");
    else
    {
        // Scan inputs from arguments
        int a, b;
        sscanf(argv[1], "%d", &a);
        sscanf(argv[2], "%d", &b);
        xor(a, b);
    }
}