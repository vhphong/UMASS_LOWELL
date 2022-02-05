// https://www.geeksforgeeks.org/friend-class-function-cpp/

/*Friend Function Like friend class, a friend function can be given special grant to access private and protected members. A friend function can be:
a) A method of another class
b) A global function*/

#include <iostream>
 
class B;
 
class A
{
	public:
	    void showB(B& );
};
 
class B
{
	private:
	    int b;
	public:
	    B()  {  b = 0; }
	    friend void A::showB(B& x); // Friend function
};
 
void A::showB(B &x)
{
    // Since show() is friend of B, it can
    // access private members of B
    std::cout << "B::b = " << x.b;
}
 
int main()
{
    A a;
    B x;
    a.showB(x);
    return 0;
}

