#!/bin/bash
# Problem-3

# Function to get xor of given two arguements
function xor () {
    a=$1
    b=$2
    axb=0
    pw=1 # Current power of 2
    echo -n "XOR of $a and $b is: "
    
    # Iterating through numbers bit by bit
    while [[ a -gt 0 ]] || [[ b -gt 0 ]]
    do
        a_binary=$(($a % 2))
        b_binary=$(($b % 2))
        xr=$(($a_binary * !$b_binary + !$a_binary * $b_binary))
        
        # Keep adding in the axb (xor result)
        axb=$(($axb + $xr * $pw))
        
        a=$(($a / 2))
        b=$(($b / 2))
        pw=$(($pw * 2))
    done
    echo $axb
}

# If arguement is not given
if [ $# -lt 2 ]
then
    echo "Error: Input not available."
else
    xor $1 $2
fi