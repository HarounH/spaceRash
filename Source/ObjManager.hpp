#ifndef Obj_Manager_hpp
#define Obj_Manager_hpp
#include "obj_Loader.hpp"
class ObjManager{
public:
	std::vector<ObjLoader*> allObjects;
	std::vector<std::vector<float> > colors;
	std::vector<sf::Image*> mBuildingImages;
	std::vector<sf::Texture*> mBuildingTextures;
	ObjManager(){};
	void LoadAllObjects(std::vector<std::string> &filepaths);
	void render(OBJECT_TYPE id);
	void drawBox(btVector3 dim , sf::Texture* tex, int c);
	void drawEndpoint(btVector3 dim);
	void drawDebris(btVector3);
	~ObjManager(){
		for(int i=0;i<mBuildingTextures.size();++i){
			if(!(!(mBuildingTextures[i]))) { delete mBuildingTextures[i]; }
			delete mBuildingImages[i];
			delete allObjects[i];
		}
	}
};
#endif