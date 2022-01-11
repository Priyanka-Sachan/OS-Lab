#!/bin/bash
# Problem-3

# If all arguements are not given.
if [ $# -lt 2 ]
then
    echo "Error: Invalid number of arguments."
else
    file_name=$1
    min_lines=$2
    num_of_lines=0
    # Iterating through lines in given file (assumed here that lines refer to new lines (\n))
    while read -r line || [ -n "$line" ]
    do
        ((num_of_lines++))
    done  < "$file_name"
    echo "Number of lines in $file_name : $num_of_lines"
    # Removing file if number of lines less than minimum lines given.
    if [ $num_of_lines -lt $min_lines ]
    then
        echo "Deleting $file_name ..."
        rm -f $file_name
    fi
fi