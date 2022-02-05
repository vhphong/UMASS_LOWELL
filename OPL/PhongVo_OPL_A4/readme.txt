Name: Phong Vo
Email: Phong_Vo@student.uml.edu	
Student ID: 01790283 
My partner: 

Degrees of success: 100%
Commands used:

pvo@cs3:~/OPL/PhongVo_OPL_A4$ ls
A4-tests.cpp  test1.cpp  test3.cpp  test5.cpp  test7.cpp  test9.cpp
Makefile      test2.cpp  test4.cpp  test6.cpp  test8.cpp  tombstones.h
pvo@cs3:~/OPL/PhongVo_OPL_A4$ make
g++ -o test1.o test1.cpp
g++ -o test2.o test2.cpp
g++ -o test3.o test3.cpp
g++ -o test4.o test4.cpp
g++ -o test5.o test5.cpp
g++ -o test6.o test6.cpp
g++ -o test7.o test7.cpp
g++ -o test8.o test8.cpp
g++ -o test9.o test9.cpp
g++ -o A4-tests.o A4-tests.cpp
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test1.o
test1: OK
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test2.o
Dangling Reference Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test3.o
Memory Leak Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test4.o
Dangling Reference Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test5.o
Memory Leak Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test6.o
Memory Leak Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test7.o
Dangling Reference Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test8.o
Dangling Reference Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./test9.o
*ptr == 12, *bar == 12 (both should be 12)
tc->a == 14, tc->b == 3.14159 (should be 14 and 3.14159)

About to use the free() friend function - beware of SEGFAULTs...
Dangling Reference Exception!
pvo@cs3:~/OPL/PhongVo_OPL_A4$ ./A4-tests.o
*ptr == 12, *bar == 12 (both should be 12)
tc->a == 14, tc->b == 3.14159 (should be 14 and 3.14159)

About to use the free() friend function - beware of SEGFAULTs...
Dangling Reference Exception!

----------------------
All code and commands were performed successfully.
The program were created by modifying the file "tombstones.h". The file has two functions which are for memory leaks (checked if ptr->referenceCounting == 0) and dangling (checked if ptr->rip).
We created int bool and pointer after building the class has been created. Our program allows int-to-Pointer comparisons. The copy constructor is used for the normal pointer. The destructor sets the the pointer to zero and decreases the reference counting. We also checked if the tombstone is used or not. If not, we delete the pointer then set the tombstone to rip.
