#!/bin/bash
# Problem-1

# If arguement is not given
if [ $# -eq 0 ]
then
    echo "Error: Input not provided."
else
    # Reading number of items(n), items(ni) and search item(S)
    n=$1
    if [ $# -lt $((n+2)) ]
    then
        echo "Error: All items/search item not present."
    else
        items=( ${@:2:n} )
        searchItem=${@:n+2:1}
        
        # Searching through the array
        searchIndex=0
        for((i=0;i<n;i++))
        do
            if [ ${items[i]} -eq $searchItem ]
            then
                searchIndex=$((i+1))
                break
            fi
        done
        
        # Check if item found or not
        if [ $searchIndex -eq 0 ]
        then
            echo "Error: Item ($searchItem) not found"
        else
            echo "Found $searchItem at index $searchIndex"
        fi
    fi
fi