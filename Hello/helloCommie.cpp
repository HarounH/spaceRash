#include <btBulletDynamicsCommon.h>
#include <iostream>

using namespace std;
int main() {
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

    //Create compund shape
    btCollisionShape* sphere1 = new btSphereShape(1);
    btCollisionShape* sphere2 = new btSphereShape(2);

    btTransform sphere1_trans(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)) ;
    btTransform sphere2_trans(btQuaternion(0, 0, 0, 1), btVector3(0, 2, 0));
        
    btDefaultMotionState* s1 = new btDefaultMotionState();
 	btDefaultMotionState* s2 = new btDefaultMotionState();
 	
    btCompoundShape* commie = new btCompoundShape();
    commie->addChildShape(sphere1_trans , sphere1);
    commie->addChildShape(sphere2_trans , sphere2);

    int n = commie->getNumChildShapes();
    cout << n << "\n";
    for(int i=0; i<n ; ++i) {
        btCollisionShape* s = commie->getChildShape(i);
        cout << s->getName();
        btTransform t = commie->getChildTransform(i);
    }
 	btScalar mass = 1;
    //done with compound shape.

    btDefaultMotionState* compound_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo compoundCI(0 , compound_state , commie , btVector3(0,0,0));
    btRigidBody* body = new btRigidBody(compoundCI);
    //now to create motion state.
    dynamicsWorld->addRigidBody(body);
    return 0 ;
}