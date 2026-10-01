#!/bin/bash

total=100

showTotal() {
	echo "Total inside function: $total"
}

echo "Total outside function: $total"

showTotal
