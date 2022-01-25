# ASSIGNMENT-2

### Problem 1
sudo chmod u+rx P1.sh

```
> ./P1.sh 5 3 4 8 3 1 
Error: All items/search item not present.
```
```
> ./P1.sh 5 3 4 8 3 1 3
Found 3 at index 1
```
---

### Problem 2
sudo chmod u+rx P2.sh
```
> ./P2.sh 4
 Answer is: 120
```
```
> ./P2.sh 11
 Answer is: 1117670400
```
---

### Problem 3
sudo chmod u+rx P3.sh

```
> ./P3.sh 3 7
XOR of 3 and 7 is: 4
```
```
> ./P3.sh 345 678
XOR of 345 and 678 is: 1023
```
### Time Analysis for Shell vs C program

**Shell Program**
```
> time ./P3.sh 345 678
XOR of 345 and 678 is: 1023

real    0m0.007s
user    0m0.004s
sys     0m0.003s
```

**C Program**
```
> gcc P3.c -o P3
> time ./P3 345 678
XOR of 345 and 678 is: 1023

real    0m0.003s
user    0m0.000s
sys     0m0.003s
```
---

### Problem 4
sudo chmod u+rx P4.sh
Note: Password should be quotes/double quotes (due to special characters).

```
> ./P4.sh 'Password99'
<Invalid Password>
```
```
> ./P4.sh 'Password99>'
<Valid Password>
```
---