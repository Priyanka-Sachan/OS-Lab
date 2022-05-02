Name : Priyanka Sachan  
Roll Number : 1901CS43  
Operating Systems Lab (CS342)  

# ASSIGNMENT-9

### Problem 1
g++ p1.cpp -o p1
```
> ./p1
Frame Count: 3
Enter a page sequence (enter a character key to stop): 
4 7 6 1 7 6 1 2 7 2
f
Best Page Replacement Algorithms: OPTIMAL

F1      F2      F3
X       X       X       at t = 0
4       X       X       at t = 1
4       7       X       at t = 2
4       7       6       at t = 3
1       7       6       at t = 4
1       7       6       at t = 5
1       7       6       at t = 6
1       7       6       at t = 7
2       7       6       at t = 8
2       7       6       at t = 9
2       7       6       at t = 10
#Page Faults: 5

```
---

### Problem 2
g++ p2.cpp -o p2
```
> ./p2
Frame Count: 3
Enter a page sequence (enter a character key to stop): 
4 7 6 1 7 6 1 2 7 2
f
Second Chance Page Replacement Algorithm Used.
#Page Faults: 6
```
---