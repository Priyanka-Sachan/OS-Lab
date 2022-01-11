#!/bin/bash
# Problem-2

# If arguement is not given.
if [ $# -lt 2 ]
then
    echo "Error: Invalid number of arguments."
    # If arguements are invalid
elif [ $1 -gt $2 ]
then
    echo "Error: First number is greater than second number."
else
    # Storing the arguements in variable - n1 and n2.
    n1=$1
    n2=$2
    
    # Iterating from n1 to n2
    while [ $n2 -ge $n1 ]
    do
        # Printing the number
        echo -n "$n1 "
        n1=$(($n1+1))
    done
    echo ""
fi