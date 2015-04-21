#ifndef obj_Loader_hpp 
#define obj_Loader_hpp

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include "helpers.hpp"


struct coordinate{
	float x,y,z;
	coordinate(float ,float,float);
};


struct material{
        float alpha,ns,ni;      //some property, alpha, shininess, and some other, which we not used
        float diff[3],amb[3],spec[3];    //the color property (diffuse, ambient, specular)
        int illum;      //illum - we not use it
        sf::Texture* texture;    
        material(float al,float n,float ni2,float* d,float* a,float* s,int i,sf::Texture *t);
};
struct face{
        int numV,numT,numN;      // Square Face or triangular face        
        std::vector<int> vertices;   //indexes for every vertex, which makes the face, starting from 1
        std::vector<int> texcoord;        //indexes for every texture coordinate that is in the face, starting from 1 
        std::vector<int> normals;
        material* mat;                //the index for the material, which is used by the face
        face(std::vector<int>& v,std::vector<int>& tex,std::vector<int>& n,material* m,bool f);   
        ~face(){
        	delete mat;
        }  
        bool four;
};
struct texcoord{
	float u,v;
	texcoord(float a,float b);
};

class ObjLoader{
	std::string name;
	SpaceObject* fighter;
	std::vector<coordinate*> vertices; 
	std::vector<face*> faces;
	std::vector<coordinate* > normals;
	std::vector<unsigned int> texture;
	//std::vector<materials*> materials;
	std::unordered_map<std::string,material*> materials;
	std::vector<texcoord*> textureCoordinates;
	bool ismaterial,isnormals,istexture; 
	bool loadTexture(const char* filename,sf::Texture* &);
	void clean();
	int ID;
public:
	
	ObjLoader(std::string Name);
	~ObjLoader(){
		clean();
	};
	int LoadObjectFile(const char* filename);
	int LoadMaterialsFile(const char* filename);
	int returnID();
	void render();
};
#endif