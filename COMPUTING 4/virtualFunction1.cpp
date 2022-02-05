// https://practice.geeksforgeeks.org/problems/difference-between-virtual-and-pure-virtual-functions

#include <iostream>
using namespace std;
class A{
	public:
	virtual void show(){
		cout<<"hello from base";
	}
};

class B:public A{
	public:
	void show(){
		cout<<"hello from child";
	}
};

int main(){
  A *ptr a1;
  ptr=a1;
  B b1;
  ptr->show();   //hello from base
  ptr=b1;
  ptr->show();   //hello from child
}
