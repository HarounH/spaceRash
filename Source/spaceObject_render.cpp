#ifndef SPACE_OBJECT_RENDER_CPP
#define SPACE_OBJECT_RENDER_CPP

#include "spaceObject.hpp"
/** file with functions for rendering things. */
void SpaceObject::render(bool dflag,ObjManager* mObjManager) {
	
    btTransform trans_com;
    body->getMotionState()->getWorldTransform(trans_com);
    float mat_gl[16];
    trans_com.getOpenGLMatrix(mat_gl);
    glPushMatrix();
        glMultMatrixf(mat_gl);
    if (dflag) {
		if ( !(obj_type==SKYRISE_TALL||obj_type==SKYRISE_FAT) )
            render_physics(dflag);
	}
	render_geometry(mObjManager);
    wasHit = false;
    glPopMatrix();
    /* rendering lasorz. */
    for(int i=0; i<weapons.size(); ++i) {
        if ( weapons[i] != NULL) {
            weapons[i]->update(); //also draws the laser if it was shot.
        }
    }

}

void SpaceObject::render_geometry(ObjManager* mObjManager) {
    if ( wasHit ) {
        //Do something.
    }
    //----------SomeOpenGL magic required here -------------//
    mObjManager->render(obj_type);
    return;
}

void SpaceObject::render_physics(bool dflag) {
	if ( !dflag ) { //not in debug mode.
		return;
	}
	for(int i=0; i<children.size(); ++i) {
		float mat_child[16];
		childTransform[i].getOpenGLMatrix(mat_child);
		glPushMatrix();
		glMultMatrixf(mat_child);
			btVector3 hdim = ((btBoxShape*)children[i])->getHalfExtentsWithMargin();
			drawBox(hdim);
		glPopMatrix();
	}
}

//not properly rendered.
void SpaceObject::drawBox(btVector3& dim) {
	btScalar x,y,z;
	x = dim.getX();
	y = dim.getY();
	z = dim.getZ();
    glLineWidth(1.0);
	//Back face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, -y, -z);
        glVertex3f(-x, y, -z);
        glVertex3f(x, y, -z);
        glVertex3f(x, -y, -z);
        glEnd();
        
        //Front face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, -y, z);
        glVertex3f(-x, y, z);
        glVertex3f(x, y, z);
        glVertex3f(x, -y, z);
        glVertex3f(-x, -y, z);
        glEnd();
        
        //Left face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, -y, -z);
        glVertex3f(-x, -y, z);
        glVertex3f(-x, y, z);
        glVertex3f(-x, y, -z);
        glEnd();
        
        //Right face
        glBegin(GL_LINE_LOOP);
        glVertex3f(x, -y, -z);
        glVertex3f(x, -y, z);
        glVertex3f(x, y, z);
        glVertex3f(x, y, -z);
        glEnd();
        
        //Top face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, y, -z);
        glVertex3f(x, y, -z);
        glVertex3f(x, y, z);
        glVertex3f(-x, y, z);
        glEnd();
        
        //Bottom face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-x, -y, -z);
        glVertex3f(x, -y, -z);
        glVertex3f(x, -y, z);
        glVertex3f(-x, -y, z);
        glEnd();
}
#endif