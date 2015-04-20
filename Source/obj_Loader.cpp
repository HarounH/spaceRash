#include "obj_Loader.hpp"
//----------------TODO Populate Render() and loadTexture(). And also, test LoadObjectFile---------------------//
        coordinate::coordinate(float a,float b,float c){
                x = a;y=b;z=c;
        }
	face::face(std::vector<int>& v,std::vector<int>& tex,std::vector<int>& n,material* m){
                numV = v.size();
                numT = tex.size();
                numN = n.size();
                for(int i=0;i<v.size();i++){
                        vertices.push_back(v[i]);
                }
                for(int i=0;i<tex.size();i++){
                        texcoord.push_back(v[i]);
                }
                for(int i=0;i<n.size();i++){
                        normals.push_back(v[i]);
                }
                mat  = m;
        }
       
        material::material(float al,float n,float ni2,float* d,float* a,float* s,int i,int t)
        {
                alpha=al;
                ni=ni2;
                ns=n;
                diff[0]=d[0];
                diff[1]=d[1];
                diff[2]=d[2];
               
                amb[0]=a[0];
                amb[1]=a[1];
                amb[2]=a[2];
               
                spec[0]=s[0];
                spec[1]=s[1];
                spec[2]=s[2];
               
                illum=i;
                texture=t;
        }
           //nothing to explain here
        texcoord::texcoord(float a,float b)
        {
                u=a;
                v=b;
        }
 
int ObjLoader::LoadMaterialsFile(const char* filename){
        std::ifstream mtlin(filename);
        if(!mtlin.is_open()){
                std::cout<<"Error cannot open materials file "<<filename<<"\n";
                clean();
                return -1;
        }
        ismaterial = true;
        std::vector<std::string> tmp;
        char line[200];
        while(!mtlin.eof()){
                mtlin.getline(line,200);
                tmp.push_back(line);
        }
        char name[200];
        char fileNm[200];
        float amb[3],diff[3],spec[3],alpha,ns,ni;
        int illum;
        unsigned int texture;
        bool ismat = false;
        strcpy(fileNm,"\0");
        for(int i=0;i<tmp.size();i++){
                if(tmp[i][0]=='#')
                        continue;
                if(tmp[i][0]=='n' && tmp[i][1]=='e' && tmp[i][2]=='w'){
                        if(ismat){
                                std::string tName = name;
                                if(strcmp(fileNm,"\0")!=0){
                                        materials[tName] =  new material(alpha,ns,ni,diff,amb,spec,illum,texture);
                                        strcpy(fileNm,"\0");
                                }
                                else{
                                        materials[tName] =  new material(alpha,ns,ni,diff,amb,spec,illum,-1);
                                }
                        }
                        ismat = false;
                        sscanf(tmp[i].c_str(),"newmtl %s",name);
                }
                else if(tmp[i][0]=='N' && tmp[i][1]=='s'){
                        sscanf(tmp[i].c_str(),"Ns %f",&ns);
                        ismat = true;
                }
                else if(tmp[i][0]=='K' && tmp[i][1]=='a'){
                        sscanf(tmp[i].c_str(),"Ka %f %f %f",&amb[0],&amb[1],&amb[2]);
                        ismat = true;
                }
                else if(tmp[i][0]=='K' && tmp[i][1]=='d'){
                        sscanf(tmp[i].c_str(),"Kd %f %f %f",&diff[0],&diff[1],&diff[2]);
                        ismat = true;
                }
                else if(tmp[i][0]=='K' && tmp[i][1]=='s'){
                        sscanf(tmp[i].c_str(),"Ks %f %f %f",&spec[0],&spec[1],&spec[2]);
                        ismat = true;
                }
                else if(tmp[i][0]=='N' && tmp[i][1] == 'i'){
                        sscanf(tmp[i].c_str(),"Ni %f",&ni);
                        ismat = true;
                }
                else if(tmp[i][0]=='d' && tmp[i][1]==' '){
                        sscanf(tmp[i].c_str(),"d %f",&alpha);
                        ismat=true;
                }
                else if(tmp[i][0]=='i' && tmp[i][1]=='l'){
                        sscanf(tmp[i].c_str(),"illum %d",&illum);
                        ismat=true;
                }
                else if(tmp[i][0]=='m' && tmp[i][1]=='a'){
                        sscanf(tmp[i].c_str(),"map_Kd %s",fileNm);
                        std::cout<<fileNm<<"\n";
                        texture = loadTexture(fileNm);
                        if(texture == -1)
                                strcpy(fileNm,"\0");
                        ismat = true;
                }

        }
        if(ismat){
                std::string tName = name;
                if(strcmp(fileNm,"\0")!=0){
                        materials[tName] = new material(alpha,ns,ni,diff,amb,spec,illum,texture);
                }
                else{
                        materials[tName] = new material(alpha,ns,ni,diff,amb,spec,illum,-1);
                }
        }
        return 0;
}

int ObjLoader::LoadObjectFile(const char* filename){
        std::ifstream in(filename);
        if(!in.is_open()){
                std::cout<<" Could not open OBJ file "<<filename<<"\n";
                return -1;
        }
        std::string buff;
        material* currmat = NULL;
        float tx,ty,tz;
        std::vector<std::string*> coord; // every line of file written onto memory
        while(getline(in,buff)){
                coord.push_back(new std::string(buff));
        }

        for(int i=0;i<coord.size();i++){
                if((*coord[i])[0]=='#')
                        continue;
                if((*coord[i])[0]=='v'){
                        switch((*coord[i])[1]){
                                case ' ': sscanf(coord[i]->c_str(),"v %f %f %f",&tx,&ty,&tz);
                                          vertices.push_back(new coordinate(tx,ty,tz));
                                          break;
                                case 'n': sscanf(coord[i]->c_str(),"vn %f %f %f",&tx,&ty,&tz);
                                          normals.push_back(new coordinate(tx,ty,tz));
                                          break;
                                case 't': sscanf(coord[i]->c_str(),"vt %f %f",&tx,&ty);
                                          textureCoordinates.push_back(new texcoord(tx,ty));
                                          break;
                                default: ;
                        }
                }
                else if((*coord[i])[0]=='u' && (*coord[i])[1]=='s' && (*coord[i])[2]=='e' && (*coord[i])[3]=='l'){
                        char fileNm[200];
                        sscanf(coord[i]->c_str(),"mtllib %s",fileNm);
                        LoadObjectFile(fileNm);
                }
                else if((*coord[i])[0]=='u' && (*coord[i])[1]=='s' && (*coord[i])[2]=='e'){
                        char matName[200];
                        sscanf(coord[i]->c_str(),"usemtl %s",matName);
                        std::string tmpmatName(matName);
                        currmat = materials[matName];
                }
                else if((*coord[i])[0]=='f'){
                        if(std::count(coord[i]->begin(),coord[i]->end(),' ')==4){
                                std::vector<int> v(4);
                                std::vector<int> n;
                                std::vector<int> t;
                                int countS = std::count(coord[i]->begin(),coord[i]->end(),'/');
                                if(countS==0){
                                        sscanf(coord[i]->c_str(),"f %d %d %d %d",&v[0],&v[1],&v[2],&v[3]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==8 && coord[i]->find("//")!=std::string::npos){
                                        n.resize(4);
                                        sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&v[0],&n[0],&v[1],&n[1],&v[2],&n[2],&v[3],&n[3]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==4){
                                        t.resize(4);
                                        sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d %d/%d",&v[0],&t[0],&v[1],&t[1],&v[2],&t[2],&v[3],&t[3]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==8 && coord[i]->find("//")==std::string::npos){
                                        t.resize(4);
                                        n.resize(4);
                                        sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&v[0],&t[0],&n[0],&v[1],&t[1],&n[1],&v[2],&t[2],&n[2],&v[3],&t[3],&n[3]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                        }
                        else if(std::count(coord[i]->begin(),coord[i]->end(),' ')==3){
                                std::vector<int> v(3);
                                std::vector<int> n;
                                std::vector<int> t;
                                int countS = std::count(coord[i]->begin(),coord[i]->end(),'/');
                                if(countS==0){
                                        sscanf(coord[i]->c_str(),"f %d %d %d",&v[0],&v[1],&v[2]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==8 && coord[i]->find("//")!=std::string::npos){
                                        n.resize(3);
                                        sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&v[0],&n[0],&v[1],&n[1],&v[2],&n[2]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==4){
                                        t.resize(3);
                                        sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d",&v[0],&t[0],&v[1],&t[1],&v[2],&t[2]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                                else if(countS==8 && coord[i]->find("//")==std::string::npos){
                                        t.resize(3);
                                        n.resize(3);
                                        sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&v[0],&t[0],&n[0],&v[1],&t[1],&n[1],&v[2],&t[2],&n[2]);
                                        faces.push_back(new face(v,t,n,currmat));
                                }
                        }
                }

        }
        if(materials.size()==0)
                ismaterial=false;
        else
                ismaterial=true;
        for(int i=0;i<coord.size();i++){
                delete coord[i];
        }
        return 0;

}

void ObjLoader::render(){

}

void ObjLoader::clean(){
        for(int i=0;i<faces.size();i++){
                delete faces[i];
        }
        for(int i=0;i<normals.size();i++){
                delete normals[i];
        }
        for(int i=0;i<vertices.size();i++){
                delete vertices[i];
        }
        for(int i=0;i<textureCoordinates.size();i++){
                delete textureCoordinates[i];
        }
       for(std::unordered_map<std::string,material*> ::const_iterator it=materials.begin();it!=materials.end();it++){
                delete it->second;
        }
        materials.clear();
        faces.clear();
        normals.clear();
        vertices.clear();
}


unsigned int ObjLoader::loadTexture (const char* filename){
        return 0;
}

ObjLoader::ObjLoader(std::string Name){
        name = Name;
        ismaterial=isnormals=istexture = false;
        vertices.push_back(NULL);
        normals.push_back(NULL);
        textureCoordinates.push_back(NULL);
}