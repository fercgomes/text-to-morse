#!/bin/bash

test_files=("bible.txt" "godfather.txt" "gutenberg-encyclopedia.txt" "lesmiserables.txt" "warpeace.txt")

for i in "${test_files[@]}"
do
	echo "Executando conversor no arquivo $i..."
	./txtToMorse -t TabelaMorse.txt -i test-files/$i -o out-$i
	./txtToMorse -t TabelaMorse.txt -i test-files/$i -o out-$i -s
done
