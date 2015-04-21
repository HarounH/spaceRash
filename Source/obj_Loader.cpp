#ifndef obj_Loader_cpp 
#define obj_Loader_cpp


#include "obj_Loader.hpp"


//----------------TODO Populate Render() and loadTexture(). And also, test LoadObjectFile---------------------//
coordinate::coordinate(float a,float b,float c){
    x = a;y=b;z=c;
}
face::face(std::vector<int>& v,std::vector<int>& tex,std::vector<int>& n,material* m,bool f){
        numV = v.size();
        numT = tex.size();
        numN = n.size();
        for(int i=0;i<v.size();i++){
                vertices.push_back(v[i]);
        }
        for(int i=0;i<tex.size();i++){
                texcoord.push_back(tex[i]);
        }
        for(int i=0;i<n.size();i++){
                normals.push_back(n[i]);
        }
        mat  = m;
        four = f;
}
face::~face(){
     mat=NULL;
}
material::material(float al,float n,float ni2,float* d,float* a,float* s,int i,sf::Texture* t){
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
material::~material(){
    delete texture;
}
void material::print(bool x) {
    if(x) {
        cout << "alpha,ns,ni=" << alpha << "," << ns << "," << ni << "\n";
        cout << "diff{" << diff[0] << "," << diff[1] << "," << diff[2] << "}\n";
        cout << "amb{" << amb[0] << "," << amb[1] << "," << amb[2] << "}\n";
        cout << "spec{" << spec[0] << "," << spec[1] << "," << spec[2] << "}\n";
        cout << (!texture) << "\n";
    }
}
   //nothing to explain here
texcoord::texcoord(float a,float b){
        u=a;
        v=b;
        //-----------POSSIBLE SOURCE OF ERROR-----------------//
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

    mtlin.close();
    char name[200];
    char fileNm[200];
    float amb[3],diff[3],spec[3],alpha,ns,ni;
    int illum;
    sf::Texture* texture = NULL;
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
                                    texture = NULL;
                                    strcpy(fileNm,"\0");
                            }
                            else{
                                    materials[tName] =  new material(alpha,ns,ni,diff,amb,spec,illum,NULL);
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
                    loadTexture(fileNm,texture);
                    if(texture == NULL)
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
                    materials[tName] = new material(alpha,ns,ni,diff,amb,spec,illum,NULL);
            }
    }
    delete texture;
    return 0;
}

int ObjLoader::LoadObjectFile(const char* filename){ //works.
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
    in.close();
    for(int i=0;i<coord.size();i++){
            if((*coord[i])[0]=='#'){
                    continue;
            } else if ( (*coord[i])[0] == 'o' ) { //its trying to name a subcomponent of the body.
                continue;
            }
            if((*coord[i])[0]=='v'){
                    switch((*coord[i])[1]){
                            case ' ': sscanf(coord[i]->c_str(),"v %f %f %f",&tx,&ty,&tz);
                                      vertices.push_back(new coordinate(tx,ty,tz));
                                      break;
                            case 'n': sscanf(coord[i]->c_str(),"vn %f %f %f",&tx,&ty,&tz);
                                      normals.push_back(new coordinate(tx,ty,tz));
                                      isnormals = true;
                                      break;
                            case 't': sscanf(coord[i]->c_str(),"vt %f %f",&tx,&ty);
                                      textureCoordinates.push_back(new texcoord(tx,ty));
                                      istexture = true;
                                      break;
                            default: ;
                    }
            }
            else if((*coord[i])[0]=='m' && (*coord[i])[1]=='t' && (*coord[i])[2]=='l' && (*coord[i])[3]=='l'){
                    char fileNm[200];
                    sscanf(coord[i]->c_str(),"mtllib %s",fileNm);
                    LoadMaterialsFile(fileNm);
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
                                    faces.push_back(new face(v,t,n,currmat,true));
                            }
                            else if(countS==8 && coord[i]->find("//")!=std::string::npos){
                                    n.resize(4);
                                    sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&v[0],&n[0],&v[1],&n[1],&v[2],&n[2],&v[3],&n[3]);
                                    faces.push_back(new face(v,t,n,currmat,true));
                            }
                            else if(countS==4){
                                    t.resize(4);
                                    sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d %d/%d",&v[0],&t[0],&v[1],&t[1],&v[2],&t[2],&v[3],&t[3]);
                                    faces.push_back(new face(v,t,n,currmat,true));
                            }
                            else if(countS==8 && coord[i]->find("//")==std::string::npos){
                                    t.resize(4);
                                    n.resize(4);
                                    sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&v[0],&t[0],&n[0],&v[1],&t[1],&n[1],&v[2],&t[2],&n[2],&v[3],&t[3],&n[3]);
                                    faces.push_back(new face(v,t,n,currmat,true));
                            }
                    }
                    else if(std::count(coord[i]->begin(),coord[i]->end(),' ')==3){
                            std::vector<int> v(3);
                            std::vector<int> n;
                            std::vector<int> t;
                            int countS = std::count(coord[i]->begin(),coord[i]->end(),'/');
                            if(countS==0){
                                    sscanf(coord[i]->c_str(),"f %d %d %d",&v[0],&v[1],&v[2]);
                                    faces.push_back(new face(v,t,n,currmat,false));
                            }
                            else if(countS==8 && coord[i]->find("//")!=std::string::npos){
                                    n.resize(3);
                                    sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&v[0],&n[0],&v[1],&n[1],&v[2],&n[2]);
                                    faces.push_back(new face(v,t,n,currmat,false));
                            }
                            else if(countS==4){
                                    t.resize(3);
                                    sscanf(coord[i]->c_str(),"f %d/%d %d/%d %d/%d",&v[0],&t[0],&v[1],&t[1],&v[2],&t[2]);
                                    faces.push_back(new face(v,t,n,currmat,false));
                            }
                            else if(countS==8 && coord[i]->find("//")==std::string::npos){
                                    t.resize(3);
                                    n.resize(3);
                                    sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&v[0],&t[0],&n[0],&v[1],&t[1],&n[1],&v[2],&t[2],&n[2]);
                                    faces.push_back(new face(v,t,n,currmat,false));
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
    //--------------E TOH NA HO RAHA----------------//
    // ID = glGenLists(1);
    // glNewList(ID,GL_COMPILE);
    material* mat = NULL;
    for(int i=0;i<faces.size();i++){
        glPushMatrix();
        if(mat != faces[i]->mat && ismaterial){
            float diffuse [] = {faces[i]->mat->diff[0],faces[i]->mat->diff[1],faces[i]->mat->diff[2],1.0};
            float ambient [] = {faces[i]->mat->amb[0],faces[i]->mat->amb[1],faces[i]->mat->amb[2],1.0};
            float specular [] = {faces[i]->mat->spec[0],faces[i]->mat->spec[1],faces[i]->mat->spec[2],1.0};
            glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
            mat = faces[i]->mat;
            if(mat->texture!=NULL){
                cout << "binding texture hi\n";
                glEnable(GL_TEXTURE_2D);
                sf::Texture::bind(faces[i]->mat->texture);
            }
            else{
                glDisable(GL_TEXTURE_2D);
            }
           
        }
        if(faces[i]->four){
            
            glBegin(GL_QUADS);
                if(isnormals){
                    glNormal3f(normals[faces[i]->normals[0]]->x,normals[faces[i]->normals[1]]->y,normals[faces[i]->normals[2]]->z);
                }
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL)  {//if there are textures
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[0]]->u,textureCoordinates[faces[i]->texcoord[0]]->v);      //set the texture coorinate
                }
                glVertex3f(vertices[faces[i]->vertices[0]]->x,vertices[faces[i]->vertices[0]]->y,vertices[faces[i]->vertices[0]]->z);
           
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL) {
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[1]]->u,textureCoordinates[faces[i]->texcoord[1]]->v);
                }
                glVertex3f(vertices[faces[i]->vertices[1]]->x,vertices[faces[i]->vertices[1]]->y,vertices[faces[i]->vertices[1]]->z);
           
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL) {
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[2]]->u,textureCoordinates[faces[i]->texcoord[2]]->v);
                }
                glVertex3f(vertices[faces[i]->vertices[2]]->x,vertices[faces[i]->vertices[2]]->y,vertices[faces[i]->vertices[2]]->z);
           
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL) {
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[3]]->u,textureCoordinates[faces[i]->texcoord[3]]->v);
                }
                glVertex3f(vertices[faces[i]->vertices[3]]->x,vertices[faces[i]->vertices[3]]->y,vertices[faces[i]->vertices[3]]->z);
                
            glEnd();

        }else{
            glBegin(GL_TRIANGLES);
                if(isnormals){
                    glNormal3f(normals[faces[i]->normals[0]]->x,normals[faces[i]->normals[0]]->y,normals[faces[i]->normals[0]]->z);
                }
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL)  {//if there are textures 
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[0]]->u,textureCoordinates[faces[i]->texcoord[0]]->v);      //set the texture coorinate
                }
                glVertex3f(vertices[faces[i]->vertices[0]]->x,vertices[faces[i]->vertices[0]]->y,vertices[faces[i]->vertices[0]]->z);
           
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL) {
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[1]]->u,textureCoordinates[faces[i]->texcoord[1]]->v);
                }
                glVertex3f(vertices[faces[i]->vertices[1]]->x,vertices[faces[i]->vertices[1]]->y,vertices[faces[i]->vertices[1]]->z);
           
                if(faces[i]->texcoord.size()!=0 && faces[i]->mat!=NULL) {
                    glTexCoord2f(textureCoordinates[faces[i]->texcoord[2]]->u,textureCoordinates[faces[i]->texcoord[2]]->v);
                }
                glVertex3f(vertices[faces[i]->vertices[2]]->x,vertices[faces[i]->vertices[2]]->y,vertices[faces[i]->vertices[2]]->z);
                
            glEnd();
        }
    sf::Texture::bind(NULL);
    glPopMatrix();
    }
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
           delete  it->second;
    }
    materials.clear();
    faces.clear();
    normals.clear();
    vertices.clear();
}

int ObjLoader::returnID(){
    return ID;
}
bool ObjLoader::loadTexture (const char* filename,sf::Texture* &tex){
    //----------ERROR POSSIBLE HERE---------------------//
    sf::Image img;
    if(!img.loadFromFile(filename)){
        cout << " Couldn't Load Image \n";
        return false;
    }
    tex = new sf::Texture;
    if(!tex->loadFromImage(img)){
        cout << "Couldn't Load Texture from image. \n";
        return false;
    }   
    return true;
}

ObjLoader::ObjLoader(std::string Name){
    name = Name;
    ismaterial=isnormals=istexture = false;
    vertices.push_back(NULL);
    normals.push_back(NULL);
    textureCoordinates.push_back(NULL);
}

void ObjLoader::print(bool debugm) {
    cout << "name=" << name << "\n";
    cout << "\tID=" << ID << "\n";
    cout << "nvertices=" << vertices.size() << "\n";
        cout << "\tvertices are @" << "\n";
        for(int i=0; i<vertices.size(); ++i) {
            if(!vertices[i]) {
                cout << "NULL VERTEX :(";
            } else {
                cout << vertices[i]->x << "," << vertices[i]->y << "," << vertices[i]->z << ")\n";
            }
        }
    cout << "nfaces=" << faces.size() << "\n";
    cout << "nNormals=" << normals.size() << "\n";
    cout << "ntexture=" << texture.size() << "\n";
    cout << "nmaterials=" << materials.size() << "\n";
    cout << "is(mat,normal,tex)=" << ismaterial << isnormals << istexture << ")\n";

    for( auto i =materials.begin(); i!= materials.end(); ++i) {
        i->second->print(debugm);
    }
}

#endif