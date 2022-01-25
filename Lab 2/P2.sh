#!/bin/bash
# Problem-2

# Function to get sum of primes less or equal to given arguement
function PrimeNoLessThan(){
    num=$1
    if [ $num -gt 1 ]
    then
        count=$num
        for((i=2;i<num;i++))
        do
            if [ $(($num%$i)) -eq 0 ]
            then
                count=0
            fi
        done
        prime=$(($count + $(PrimeNoLessThan $(($num-1)))))
    else
        prime=0
    fi
    echo $prime
}

# Function to get factorial of given arguement
function fact(){
    num=$1
    fact=1
    if [ $num -gt 1 ]
    then
        fact=$(($num*$(fact $(($num-1)))))
    fi
    echo $fact
}

# If arguement is not given
if [ $# -eq 0 ]
then
    echo "Error: Input not provided."
else
    num=$1
    echo " Answer is: $(($(fact $num)*$(PrimeNoLessThan $num)))"
fi