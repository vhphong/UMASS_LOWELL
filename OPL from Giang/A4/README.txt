Assignment 4A 

Name: Muhammad Muneeb 

I worked With Hylton Carboo on this assignment

Compiling steps and outputs of our test.
Do make and you can test like we did. 

make

./test1.o
foo1: OK

./test2.o
Therer is Dangling Reference Excep!

./test3.o
Test3: OK

./test4.o
Therer is Dangling Reference Excep!

./test5.o
A Memory Leak Excep!

./test6.o
A Memory Leak Excep!

./test7.o
Therer is Dangling Reference Excep!

./test8.o
Therer is Dangling Reference Excep!


/////// Test 9 is the test profeser provided us.   //////
 
./test9.o
*ptr == 12, *bar == 12 (both should be 12)
tc->a == 14, tc->b == 3.14159 (should be 14 and 3.14159)

About to use the free() friend function - beware of SEGFAULTs...
Therer is Dangling Reference Excep!

Everything seems to work fine for us. 
We started by modifying the code in the tombstones.h. There are two functions one for memory leaks and dangling. The code will end after running into two situations.
After building the class we used Int bool and pointer for and used the default constructor. The copy constructor is used for a normal pointer. The destructor will set the pointer to zero and decrement ref counting. For the free fun we check if the tombstone is in used if its not we delete the pointer and to the obj and set the tombstone to be RIP.
The rest id compare and inequality functions with two different perimeters.
Added two different function to support the num of pointer comparison. Comments pretty much explain everything. 
