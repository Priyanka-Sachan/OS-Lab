Name : Priyanka Sachan  
Roll Number : 1901CS43  
Operating Systems Lab (CS342)  

# ASSIGNMENT-8

### Problem 1
g++ bankers_algo.cpp -o ba
```
> ./ba
Number of processes:5
Number of resources:3
Enter resource (allocated & max) for process 0:
0 1 0
7 5 3
Enter resource (allocated & max) for process 1:
2 0 0
3 2 2
Enter resource (allocated & max) for process 2:
3 0 2
9 0 2
Enter resource (allocated & max) for process 3:
2 1 1
2 2 2
Enter resource (allocated & max) for process 4:
0 0 2
4 3 3
Enter available resources:3 3 2

AVAILABLE RESOURCES: 3 3 2 
P | ALLOC_RES | MAX_RES | REQ_RES
0 | 0 1 0  | 7 5 3  | 7 4 3 
1 | 2 0 0  | 3 2 2  | 1 2 2 
2 | 3 0 2  | 9 0 2  | 6 0 0 
3 | 2 1 1  | 2 2 2  | 0 1 1 
4 | 0 0 2  | 4 3 3  | 4 3 1 

SAFE SEQUENCES
P1->P3->P0->P2->P4
P1->P3->P0->P4->P2
P1->P3->P2->P0->P4
P1->P3->P2->P4->P0
P1->P3->P4->P0->P2
P1->P3->P4->P2->P0
P1->P4->P3->P0->P2
P1->P4->P3->P2->P0
P3->P1->P0->P2->P4
P3->P1->P0->P4->P2
P3->P1->P2->P0->P4
P3->P1->P2->P4->P0
P3->P1->P4->P0->P2
P3->P1->P4->P2->P0
P3->P4->P1->P0->P2
P3->P4->P1->P2->P0
```
---