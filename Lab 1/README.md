# ASSIGNMENT-1

### Problem 1
sudo chmod u+rx P1.sh

```
> ./P1.sh  
Error: Input not provided.
```

```
> ./P1.sh 45788  
88754
```
---

### Problem 2
sudo chmod u+rx P2.sh
```
> ./P2.sh 8 3  
Error: First number is greater than second number.
```

```
> ./P2.sh 2 7  
2 3 4 5 6 7
```

```
> ./P2.sh 4 4  
4
```
---

### Problem 3
sudo chmod u+rx P3.sh

```
> ./P3.sh
Error: Invalid number of arguments.
```

```
> ./P3.sh Test/lu.txt 3
Number of lines in Test/lu.txt : 5
```

```
> ./P3.sh Test/av.txt 4
Number of lines in Test/av.txt : 3
Deleting Test/av.txt ...
```
---

### Problem 4
sudo chmod u+rx P4.sh

```
> ./P4.sh
> Enter directory path: /home/sachan/Documents/VI Semester/CS341 Operating Systems/Lab/Lab 1/Test
> Enter filename pattern: 3xyz45
> Enter the new filename: 67abc8
```

Files present were xyz.txt, 33xyz456.txt, 30xyz45.txt, 3xyz45.txt  
After execution, files were renamed as xyz.txt, 67abc8_1.txt, 30xyz45.txt, 67abc8_2.txt

---