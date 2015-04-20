
#include <iostream>
#include <glm/glm.hpp> /* glm base include. */
using namespace std;
int main() {
	glm::vec3 hi;
	glm::vec3 bye;
	hi.x = 1.0; hi.y=2.0; hi.z = 3.0;
	bye.x = 1.0; bye.y=2.0; bye.z = 3.0;
	glm::vec3 lol = hi-bye;
	cout << "(" << lol.x << "," << lol.y << "," << lol.z << ")"; //Thats how to access the coordinates.
	return 1;
}