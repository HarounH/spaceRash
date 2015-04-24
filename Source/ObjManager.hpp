#ifndef Obj_Manager_hpp
#define Obj_Manager_hpp
#include "obj_Loader.hpp"
class ObjManager{
public:
	std::vector<ObjLoader*> allObjects;
	ObjManager(){};
	void LoadAllObjects(std::vector<std::string> &filepaths);
	void render(OBJECT_TYPE id);
};
#endif