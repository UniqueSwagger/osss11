#!/bin/bash

echo "Enter numbers: "
read -a arr

if [ ${#arr[@]} -eq 0 ]; then
    echo "No numbers entered."
    exit 1
fi

echo "You entered: ${arr[@]}"

sum=0
largest=${arr[0]}
for number in "${arr[@]}"
do
    if awk "BEGIN {exit !($number > $largest)}"
    then
    	largest=$number
    fi
    sum=$(awk "BEGIN {print $sum + $number}")
done

count=${#arr[@]}
average=$(awk "BEGIN {printf \"%.2f\", $sum / $count}")

echo "Average: $average"
echo "Largest element: $largest"
