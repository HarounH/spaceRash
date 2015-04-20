#ifndef QUATER
#define QUATER

#include <iostream>
#include <string>

/* go hand in hand. */
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp> //Quaternions!


using namespace std;


typedef glm::quat Quat;
void qprint(Quat q) {
	std::cout << "quat(" << q.x << "," << q.y << "," << q.z << "," << q.w << ").";
}

int main(int argc, char** argv) {
	Quat unitquat;
	//qprint(unitquat);
	glm::vec3 e_angle(90,0,0);
	Quat aboutx(glm::radians(e_angle));
	qprint(aboutx);
	return 1;
}
#endif