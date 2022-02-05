#include <iostream>
using namespace std;

class Foo {
    public static void classMethod() 
    {
        cout << "classMethod() in Foo";
    }

    public : void instanceMethod() 
    {
        cout << "instanceMethod() in Foo";
    }
};

class Bar extends Foo {
    public static void classMethod()  
    {
        cout << "classMethod() in Bar";
    }

    public void instanceMethod()
	{
        cout << "instanceMethod() in Bar";
    }
}

class Test {
    public static void main(String[] args) {
        Foo f = new Bar();
        f.instanceMethod();
        f.classMethod();
    }
}

// The Output for this code is: instanceMethod() in Bar classMethod() in Foo

/*
* An overloaded function is a function that shares its name with one or more other functions, but which has a different parameter list. 
The compiler chooses which function is desired based upon the arguments used.

* An overridden function is a method in a descendant class that has a different definition than a virtual function in an ancestor class. 
The compiler chooses which function is desired based upon the type of the object being used to call the function.

* A redefined function is a method in a descendant class that has a different definition than a non-virtual function in an ancestor class. 
Don't do this. Since the method is not virtual, the compiler chooses which function to call based upon the static type of the object reference rather than the actual type of the object.

	Static type checking means that type checking occurs at compile time. No type information is used at runtime in that case.

	Dynamic type checking occurs when type information is used at runtime. C++ uses a mechanism called RTTI (runtime type information) to implement this. The most common example where RTTI is used is the dynamic_cast operator which allows downcasting of polymorphic types:
*/
