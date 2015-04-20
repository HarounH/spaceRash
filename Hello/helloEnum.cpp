#include <iostream>
using namespace std;

enum HELLO {
		HI1 = 1,
		HI2 = 1<<1,
		HI3 = 1<<2,

	};

int main(int argc, char** argv) {
	int dude = (HI1 | HI2) ;
	cout << dude << "\n";
	return 1;
}