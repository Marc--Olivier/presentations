#include <iostream>
#include <memory>

struct B {
	int val;
};

class A {
public:
	A(std::unique_ptr<B> b);
	~A(); // Not required unless using forward declaration for B
	const B* getB() const {
		return b.get();
	};
private:
	std::unique_ptr<B> b;
};

int main() {
	std::unique_ptr<B> b(new B{42});
	A a(std::move(b));
	// Cannot use b anymore
	std::cout << "Hello, " << a.getB()->val << "!" << std::endl;
	return 0;
}

A::A(std::unique_ptr<B> b_)
	: b(std::move(b_))
{
}

A::~A() {
}
