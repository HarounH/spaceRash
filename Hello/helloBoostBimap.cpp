#include <boost/config.hpp>
#include <string>
#include <iostream>
#include <boost/bimap.hpp>
/* Nothing special for compilation. */
typedef boost::bimap<std::string,int> bmap;
typedef bmap::value_type rtype;

int main(int argc, char** argv) {
	bmap mymap;
	mymap.insert(rtype("1s" , 1));
	mymap.insert(rtype("2s" , 2));
	mymap.insert(rtype("3s" , 3));
	mymap.insert(rtype("4s" , 4));

	std::cout << mymap.right.at(1) << " is at 1, right\n";
	return 1;
}