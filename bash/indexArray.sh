
array=("Shohidur" "Asim" "Nibir")

echo "Number of elements: ${#array[@]}"
echo "All elements: ${array[@]}"

array+=("Sinha")

echo "echo Number of elements: ${#array[@]}"
echo "All elements: ${array[@]}"

echo "First element : ${array[0]}"
echo "fourth element: ${array[3]}"
