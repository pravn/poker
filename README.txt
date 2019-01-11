BUILD
====
Use cmake

mkdir bld
cd bld
cmake <path/to/root>
make 

RUN
===
Copy inputs from <path/to/root>/inputs to run dir.
Next, rename one of the cases to input.txt

E.g. 
cp input_full_house.txt input.txt

The original case given in the problem is called input_orig.txt


Here is the output for input_full_house.txt 

placeholder@kakrafoon:~/projects/poker/bld$ ./texas 
Done reading 
KS AD 3H KC TD 
John 9H 7S 
Sam AC KH 
Becky JD QC 
===============================
Hands 
Hand name: Sam
Result:Full house 
High: KA
Score: 7
==============================
Hand name: Becky
Result: Straight 
High: A
Score: 5
==============================
Hand name: John
Result: Pair 
High: K
Kickers: A T 9 
Score: 2
==============================
Winning hands 
Hand name: Sam
Result:Full house 
High: KA

