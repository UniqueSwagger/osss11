#!/bin/bash

echo "Enter numbers: "
read -a arr

sum=0
largest=${arr[0]}

for x in "${arr[@]}"
do 
	sum=$((sum+x))
	if [ "$x" -gt "$largest" ]; then
		largest=$x
	fi
done

count=${#arr[@]}

avg=$(awk "BEGIN {printf \"%.2f\", $sum/$count}")

echo "average: $avg"
echo "Largest: $largest"
