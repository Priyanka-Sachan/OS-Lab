#!/bin/bash
# Problem-4

# If arguement is not given
if [ $# -eq 0 ]
then
    echo "Error: Input not available."
    exit 1
fi

# Storing password and length
password=$1
length=${#password}

# Characters for password matching
alpha="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
numbers="0123456789"
special="/()<>?"

# Function to check if one of the characters from the given set is present in password
function contains() {
    charSet=$1 # Given set (alphabets/numbers/special characters)
    for ((i = 0; i < $length; ++i))
    do
        for ((j = 0; j < ${#charSet}; ++j))
        do
            if [ ${password:i:1} == ${charSet:j:1} ]
            then
                echo 1
                return
            fi
        done
    done
    echo 0
    return
}

if [ $length -ge 7 ] && [ $(contains "$alpha") -eq 1 ]  && [ $(contains "$numbers") -eq 1 ] && [ $(contains "$special") -eq 1 ]
then
    echo "<Valid Password>"
else
    echo "<Invalid Password>"
fi