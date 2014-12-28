#!/usr/bin
echo "libtext_bayes by Cooler_"
echo "---------------------------------------------------------"
echo "libtext_bayes - https://github.com/CoolerVoid/libtext_bayes "
mkdir pack; cd pack
cmake ../; make; cd .. ; cp libtext_bayes.h pack; cp test.cpp pack; cd pack
cp liblibtext_bayes.so /lib
echo "================================================"
echo "Test programm at pack/test\n "
echo " $ g++ -o test test.cpp -llibtext_bayes"
echo "------------------------------------------------"
g++ -o test test.cpp -llibtext_bayes
./test
echo "look the file \"test.cpp\" to you know how to use this library..."

