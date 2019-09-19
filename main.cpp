#include <iostream>
#include"shared_ptr.h"
using namespace std;



struct Foo {
	Foo() { std::cout << "Foo()\n"; }
	~Foo() { std::cout << "~Foo()\n"; }
	Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
	Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
};

struct Fooo {
	Fooo(int n = 0) noexcept : bar(n) { std::cout << "Fooo: constructor, bar = " << bar << '\n'; }
	~Fooo() { std::cout << "Fooo: destructor, bar = " << bar << '\n'; }
	int GetBar() const noexcept { return bar; }

private:
	int bar;
};

struct D {
	void bar() { std::cout << "Call deleter D::bar()...\n"; }
	void operator()(Foo* p) const
	{
		std::cout << "Call delete from function object...\n";
		delete p;
	}
};
int main()
{
	std::cout << "shared_ptr constructor with no managed object\n";
	{
		shared_ptr<Foo> sh1;
	}

	std::cout << "shared_ptr constructor with object and test swap \n";
	{
		shared_ptr<Foo> sh2(new Foo);
		std::cout << sh2.use_count() << '\n';//1
		shared_ptr<Foo> sh3(sh2);
		std::cout << sh3.use_count() << '\n';// 2
	}

	{
		shared_ptr<Fooo> sptr(new Fooo(111));
		std::cout << "The first Fooo's bar is " << sptr->GetBar() << "\n"; // 111  
	}
}
