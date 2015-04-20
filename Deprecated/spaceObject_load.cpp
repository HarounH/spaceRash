#ifndef SPACE_OBJECT_LOAD_CPP
#define SPACE_OBJECT_LOAD_CPP


/** The load function for the object. */
bool SpaceObject::loadOBJ() {
	//Assume that the file path is in objFile.
	ifstream objf;
	objf.open(OBJFilepath);
	if ( !objf.is_open() ) {
		std::cout << " failed to open file=" << OBJFilepath << "! Please ensure its present in the correct locaiton\n";
		return false;
	}

	string next_line;
	while (objf) {
		getline(objf,next_line,'\n'); //I can set delimiters in this? cool.
		if ( next_line[0] == '#' ) { //comment line.
			continue;
		} else if ( next_line[0] == 'v' && next_line[1] == ' ' ) { //geometry vertex.
			Position vertex;
			sscanf(next_line.c_str(), "v %f %f %f" , vertex.x , vertex.y , vertex.z);
			vertex.w = 1.0;
			object_vertices.push_back(vertex);
		} else if ( next_line[0] == 'v' && next_line[1] == 'n' ) { //normal to the face?
			Direction normal;
			sscanf(next_line.c_str(), "v %f %f %f" , normal.x , normal.y , normal.z);
			normal.w = 0.0;
			object_normals.push_back(normal);
		} else if ( next_line[0] == 'v' && next_line[1] == 't' ) { //texture vertex!
			glm::vec4 tVertex;
			sscanf(next_line.c_str() , "vt %f %f" , tVertex.x, tVertex.y);
			tVertex.z = 0.0; tVertex.w = 0.0;
			object_tVertices.push_back(tVertex);
		} else if ( next_line[0] == 'f' ) { //faces?

		}
	}

}
#endif