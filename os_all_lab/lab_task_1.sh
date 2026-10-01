#!/bin/bash
array=("Shohidur" "Asim" "Nibir")
echo "Number of elements: ${#array[@]}"
echo "All elements: ${array[@]}"
array+=("Sinha")
echo "Number of elements: ${#array[@]}"
echo "All elements after adding : ${array[@]}"
echo "First element: ${array[0]}"
echo "Fourth element: ${array[3]}"

