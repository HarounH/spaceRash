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


struct coordinate{
	float x,y,z;
	coordinate(float ,float,float);
};


struct material{
        float alpha,ns,ni;      //some property, alpha, shininess, and some other, which we not used
        float diff[3],amb[3],spec[3];    //the color property (diffuse, ambient, specular)
        int illum;      //illum - we not use it
        int texture;    //the id for the texture, if there is no texture than -1
        material(float al,float n,float ni2,float* d,float* a,float* s,int i,int t);
};
struct face{
        int numV,numT,numN;      // Square Face or triangular face        
        std::vector<int> vertices;   //indexes for every vertex, which makes the face, starting from 1
        std::vector<int> texcoord;        //indexes for every texture coordinate that is in the face, starting from 1 
        std::vector<int> normals;
        material* mat;                //the index for the material, which is used by the face
        face(std::vector<int>& v,std::vector<int>& tex,std::vector<int>& n,material* m);   
        ~face(){
        	delete mat;
        }  
};
struct texcoord{
	float u,v;
	texcoord(float a,float b);
};

class ObjLoader{
	std::string name;
	
	std::vector<coordinate*> vertices; 
	std::vector<face*> faces;
	std::vector<coordinate* > normals;
	std::vector<unsigned int> texture;
	//std::vector<materials*> materials;
	std::unordered_map<std::string,material*> materials;
	std::vector<texcoord*> textureCoordinates;
	bool ismaterial,isnormals,istexture; 
	unsigned int loadTexture(const char* filename);
	void clean();
public:
	/*void displayVertices(){
		for(int i=0;i<vertices.size();i++){
			std::cout<<vertices[i]->x<<" "<<vertices[i]->y<<" "<<vertices[i]->z<<"\n";
		}
	}
	void displayMaterials(){
		for(std::unordered_map<std::string,material*> ::const_iterator it=materials.begin();it!=materials.end();it++){
			std::cout<<"\n"<<it->first<<"\n"<<it->second->alpha<<"\n"<<it->second->ns<<"\n"<<it->second->ni<<"\n"<<it->second->diff[0]<<" "<<it->second->diff[1]<<" "<<it->second->diff[2]<<"\n"<<it->second->amb[0]<<" "<<it->second->amb[1]<<" "<<it->second->amb[2]<<"\n"<<it->second->spec[0]<<" "<<it->second->spec[1]<<" "<<it->second->spec[2]<<"\n"<<it->second->illum<<"\n"<<it->second->texture<<"\n";
		}
	}*/
	ObjLoader(std::string Name);
	~ObjLoader(){
		clean();
	};
	int LoadObjectFile(const char* filename);
	int LoadMaterialsFile(const char* filename);
	void render();
};