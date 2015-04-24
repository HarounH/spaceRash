#ifndef OBJ_MANAGER_CPP
#define OBJ_MANAGER_CPP
#include "ObjManager.hpp"
#include "helpers.hpp"
void ObjManager::LoadAllObjects(std::vector<std::string> & filePaths){
	if(filePaths.size()!=4){
		std::cout<<"Improperly used filepaths ";
		return;
	}
	allObjects.push_back(new ObjLoader("TIE.FIGHTER"));
	allObjects.push_back(new ObjLoader("X Wing"));
	allObjects.push_back(new ObjLoader("SKYRISE TALL"));
	allObjects.push_back(new ObjLoader("SKYRISE FAT"));
	allObjects[0]->LoadObjectFile(filePaths[0].c_str());
	allObjects[1]->LoadObjectFile(filePaths[1].c_str());
	allObjects[2]->LoadObjectFile(filePaths[2].c_str());
	allObjects[3]->LoadObjectFile(filePaths[3].c_str());
}
void ObjManager::render(OBJECT_TYPE id){
	switch (id){
		case TIE: {
			allObjects[0]->render();
			break;
			}
		case XWING: allObjects[1]->render();
				break;
		case SKYRISE_TALL : allObjects[2]->render();
				break;
		case SKYRISE_FAT : allObjects[3]->render();
				break;
		default: break;
	}

}

#endif