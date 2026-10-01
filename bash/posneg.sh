#!/bin/bash

echo "Enter a number:"
read num

if ((num>0)) then
    echo "Positive"
else
    echo "Zero or negative"
fi
