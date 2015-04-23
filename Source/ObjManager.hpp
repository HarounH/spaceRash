#ifndef Obj_Manager_hpp
#define Obj_Manager_hpp
#include "Obj_Loader.hpp"
class ObjManager{
	std::vector<ObjLoader*> allObjects;
public:
	ObjManager(){};
	void LoadAllObjects(std::vector<std::string> &filepaths);
	void render(OBJECT_TYPE id);
};
#endif