

#include <iostream>
using namespace std;

class A{
	public:
		virtual void show()=0;
};

class B:public A{
	public:
		void show(){
			cout<<"hello";
		}
};

int main(){
	B b1;
	b1.show();   //hello
}
