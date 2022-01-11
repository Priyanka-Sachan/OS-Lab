#!/bin/bash
# Problem-4

echo -n "Enter directory path: "
read directory_path
echo -n "Enter filename pattern: "
read pattern
echo -n "Enter the new filename: "
read new_filename

# Moving to given directory
cd "$directory_path"
count=1

# Iterating through all files in directory
for file in *
do
    file_name="$(basename -- "$file")"
    # Matching filename with given pattern
    if [[ $file_name == *"${pattern}"* ]]
    then
        # Extension is assumed to be .txt (as given in assignment)
        new_file=${new_filename}_${count}.txt
        $(mv $file $new_file)
        ((count++))
    fi
done