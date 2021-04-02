#!/bin/sh

for input in ./tests/*.in
do
    output="results/"
    output+=$(basename "$input")
    output+=".out"
    echo "============================="
    echo "$input"
    echo "_____________________________"
    ./Kanban < "$input" > "$output"
    echo "............................."
done