#include <iostream>

using namespace std;

class Abstract {
public:
	void normalfunc1();
	void normalfunc2();
	virtual void notnormalfunc() = 0 ;
};

void Abstract::normalfunc1() {
	cout << "this is my normal func1 says abstract\n";
}

void Abstract::normalfunc2() {
	cout << "this is my normal func2 says abstract\n";
}

/* Its possible to override functions. cool. */
class NotAbstract : public Abstract {
public:
	void notnormalfunc() {
		cout << "this is my not normal func says NotAbstract\n";
	}
	void normalfunc2() {
		cout << "this is my normal func 2 says NotAbstract\n";		
	}
};

int main(int argc, char** argv) {
	// Abstract ab;
	NotAbstract nab;
	// ab.normalfunc();
	// ab.notnormalfunc();
	nab.normalfunc1();
	nab.normalfunc2();
	nab.notnormalfunc();
}