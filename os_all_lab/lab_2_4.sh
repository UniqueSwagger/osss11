#!/bin/bash

declare -A scores=([Ron]=10 [Asim]=20 [Nibir]=30)

echo "${!scores[@]}"
