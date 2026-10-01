#!/bin/bash

calculateSum() {
	sum=50
	echo "Sum inside function: $sum"
}

echo "Sum outside function: $sum"
calculateSum
