#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int func(){
    fork();
    fork();
    printf("Hello\t");
}

int main(){
    func();
    printf("Hello\t");
    exit(0);
}