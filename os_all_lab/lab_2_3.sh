#!/bin/bash

declare -a my_data=("Learning" "Bash variables" "GFG")

arrLength=${#my_data[@]}

echo "Total number of elements: $arrLength"

for (( i=0; i<arrLength; i++ )) 
do
	echo "Element $((i+1)) is '${my_data[$i]}' and its length is ${#my_data[$i]}"
done

echo "All elements: ${my_data[@]}"
