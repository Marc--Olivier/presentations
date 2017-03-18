#include <iostream>

struct B {
	int val;
};

class A {
public:
	A(B* b);
	~A();
private:
	B* b;
};

int main() {
	B* b = new B{42};
	A a(b);
	std::cout << "Hello, " << b->val << "!" << std::endl;
	delete b; // ?
	return 0;
}

// Code hidden in a cpp file
A::A(B* b_)
	: b(b_)
{
}

A::~A() {
	delete b;
}
