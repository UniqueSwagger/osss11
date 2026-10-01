#!/bin/bash

arr=("Shohidur" "Asim" "Nibir")

for ((i=0;i<${#arr[@]};i++))
do 
	echo "${arr[$i]}"
done
