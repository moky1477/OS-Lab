#!/bin/bash

# Define an array of numbers
numbers=(4 2 8 6 1 3)

# Get the length of the array
length=${#numbers[@]}

# Perform the Bubble Sort algorithm to sort the array in ascending order
for ((i = 0; i < length - 1; i++)); do
    for ((j = 0; j < length - i - 1; j++)); do
        if ((numbers[j] > numbers[j + 1])); then
            # Swap the elements if they are out of order
            temp=${numbers[j]}
            numbers[j]=${numbers[j + 1]}
            numbers[j + 1]=$temp
        fi
    done
done

# Display the sorted array
echo "Sorted Array in Ascending Order:"
for ((i = 0; i < length; i++)); do
    echo "${numbers[i]}"
done

