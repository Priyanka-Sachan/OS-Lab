# ASSIGNMENT -10

```
(base) sachan@CLOUD-DESK:~/Documents/VI Semester/CS341 Operating Systems/Lab/Lab 10$ g++ p.cpp -o p
(base) sachan@CLOUD-DESK:~/Documents/VI Semester/CS341 Operating Systems/Lab/Lab 10$ ./p

Enter p, v & f:8 10 4

Enter Number of range of frames already occupied:2

Enter ranges:0 2
5 7

Enter no. of queries:5

Enter query: a 64
64 bytes have allocated in frames : 3 4 8 9 
 | page | frame |
 |------|-------|
 | 0 | 3 | 
 | 1 | 4 | 
 | 2 | 8 | 
 | 3 | 9 | 
Enter query: t 43

Physical address :139
Enter query: d 1

 | page | frame |
 |------|-------|
 | 0 | 3 | 
 | 2 | 8 | 
 | 3 | 9 | 
Enter query: d 241

Invalid page number.
Enter query: a 32
32 bytes have allocated in frames : 4 10 
 | page | frame |
 |------|-------|
 | 0 | 3 | 
 | 2 | 8 | 
 | 3 | 9 | 
 | 4 | 4 | 
```