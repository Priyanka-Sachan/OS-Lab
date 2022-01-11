#!/bin/bash
# Problem-1

# If arguement is not given.
if [ $# -eq 0 ]
then
    echo "Error: Input not provided."
else
    # Storing the first arguement in num variable.
    num=$1
    numr=0
    
    # Reversing the input(num) and storing it in numr
    while [ $num -ne 0 ]
    do
        numr=$(($numr * 10 + $num % 10))
        num=$(($num / 10))
    done
    # Printing the reversed number
    echo $numr
fi