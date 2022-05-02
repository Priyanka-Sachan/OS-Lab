Name : Priyanka Sachan  
Roll Number : 1901CS43  
Operating Systems Lab (CS342)  

# ASSIGNMENT-7

### Problem 1
gcc -pthread -o P1 P1.c
```
> ./P1
Reader-0 is reading
Reader-1 is reading
Reader-3 is reading
Reader-0 completes reading
Reader-2 is reading
Reader-1 completes reading
Reader-2 completes reading
Reader-4 is reading
Reader-4 completes reading
Reader-3 completes reading
Writer-0 is writing
Writer-0 completes writing
Writer-1 is writing
Writer-1 completes writing
```
---

### Problem 2
If A then B function is called, then deadlock is possibel when A has `mutex` but waits on `data` and B has `data` and waits for `mutex` .  

To avoid deadlock, both A and B can be changed to :  
```
{
    wait(mutex);
    wait(data);
    print(“process B”)
    signal(data);
    signal(mutex);
}
```
---

### Problem 3
gcc -pthread -o P3 P3.c
```
> ./P3
Pizza services - up and running.
Student-2 - up and running
Student-3 - up and running
Student-3 ordered pizza.
Student-1 - up and running
Student-4 - up and running
Pizza made.
Pizza is delivered.
Student-6 - up and running
Student-6 ate a slice of pizza.
Student-7 - up and running
Student-7 ate a slice of pizza.
Student-2 ate a slice of pizza.
Student-5 ate a slice of pizza.
Student-3 ate a slice of pizza.
Student-3 ordered pizza.
Pizza made.
Pizza is delivered.
Student-4 ate a slice of pizza.
...
...
...
```
---
