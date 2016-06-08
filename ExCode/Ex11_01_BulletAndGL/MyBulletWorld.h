#ifndef BULLETWORLD_HH_
#define BULLETWORLD_HH_
#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>

#include "../../src/btBulletDynamicsCommon.h"

class CBulletWorld {
	
	btBroadphaseInterface* broadphase;	
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionShape* groundShape;
	btCollisionShape* ballShape;
	btCollisionShape* boxShape;
	btRigidBody* groundRigidBody;
	btRigidBody* ballRigidBody;
	btRigidBody* boxRigidBody;
	
public:

	btDiscreteDynamicsWorld* mWorld;
	btDefaultMotionState* groundMotionState;
	btDefaultMotionState* ballMotionState;
	btDefaultMotionState* boxMotionState;

public:
	void initialize();
	void draw();
	void step(float dt);

	void release();

	void moveBall();

};

#endif