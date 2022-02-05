// https://www.geeksforgeeks.org/friend-class-function-cpp/

/*Friend Class A friend class can access private and protected members of 
other class in which it is declared as friend. It is sometimes useful to allow 
a particular class to access private members of other class. 
For example a LinkedList class may be allowed to access private members of Node.*/

#include <iostream>
class A {
	private:
		int a;
	public:
		A() { a=0; }
		friend class B;	 // Friend Class
};

class B {
	private:
		int b;
	public:
		void showA(A& x) {
			// Since B is friend of A, it can access
			// private members of A
			std::cout << "A::a=" << x.a;
		}
};

int main() {
	A a;
	B b;
	b.showA(a);
	return 0;
}

