rm debug.txt
make clean
make
./txtToMorse -t TabelaMorse.txt -i test-files/TheGodfather-MarioPuzo-Chapter1-English.txt -o splay.txt -s
./txtToMorse -t TabelaMorse.txt -i test-files/TheGodfather-MarioPuzo-Chapter1-English.txt -o abp.txt
if cmp -s ./splay.txt ./abp.txt
then 
  echo "The program outputs the same value on both implementations"
  if cmp -s ./splay.txt ./test-files/TheGodfather-MarioPuzo-Chapter1-Morse.txt
  then
    echo "The output matchs the test-file"
  else
    echo "The output doesn't match the test-file"
  fi
else
  echo "The output differs depending on the implementation"
fi
