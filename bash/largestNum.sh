#!/bin/bash

echo "Enter numbers: "
read -a arr
largest=${arr[0]}
for x in "${arr[@]}"
do 
	if [ "$x" -gt "$largest" ]; then
		largest=$x
	fi
done
echo "largest: $largest"
