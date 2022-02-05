// https://stackoverflow.com/questions/44806507/c-friend-classes-and-friend-member-functions
#include <iostream>

class A{
	public:
	    friend class B;
	    //friend void B::set(int i);
	    //friend int B::get();
	    friend int function(A a);
	    A(int i);
	    void set(int i);
	    int get();
	private:
	    int i;
};

A::A(int i) : i(i){}

void A::set(int i){
    this->i = i;
}

int A::get(){
    return i;
}

class B{
	public:
	    B(A a);
	    void set(int i);
	    int get();
	private:
	    A a;
};

B::B(A a) : a(a){}

void B::set(int i){
    a.i = i;
}

int B::get(){
    return a.i;
}

int function(A a);

int main(int argc, char *argv[]){
    A a(0);
    std::cout << "in A i=" << a.get() << std::endl;
    a.set(10);
    std::cout << "in A i=" << a.get() << std::endl;
    B b(a);
    std::cout << "in B i=" << b.get() << std::endl;
    b.set(21);
    std::cout << "in B i=" << b.get() << std::endl;
    std::cout << "function returns " << function(a) << std::endl;
}

int function(A a){
    return a.i;
}
