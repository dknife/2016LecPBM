#include "MyBulletWorld.h"

void CBulletWorld::initialize() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;

	mWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	mWorld->setGravity(btVector3(0, -10, 0));

	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	ballShape = new btSphereShape(1);
	boxShape = new btBoxShape(btVector3(1,1,1));

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setRestitution(0.5);
	mWorld->addRigidBody(groundRigidBody);


	ballMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 5, 0)));
	btScalar mass = 1;
	btVector3 ballInertia(0, 0, 0);
	ballShape->calculateLocalInertia(mass, ballInertia);
	btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass, ballMotionState, ballShape, ballInertia);
	ballRigidBody = new btRigidBody(ballRigidBodyCI);
	ballRigidBody->setRestitution(1.0);
	mWorld->addRigidBody(ballRigidBody);

	boxMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(2, 3, 0)));
	btScalar boxMass = 1;
	btVector3 boxInertia(0, 0, 0);
	boxShape->calculateLocalInertia(boxMass, boxInertia);
	btRigidBody::btRigidBodyConstructionInfo boxRigidBodyCI(boxMass, boxMotionState, boxShape, boxInertia);
	boxRigidBody = new btRigidBody(boxRigidBodyCI);
	boxRigidBody->setRestitution(0.75);
	mWorld->addRigidBody(boxRigidBody);

}

void CBulletWorld::step(float dt) {
	mWorld->stepSimulation(dt, 10, 1.0/60.0);
}

void CBulletWorld::draw() {
	btTransform trans;
	btVector3 loc;
	btMatrix3x3 mat;
	GLfloat glMat[16];

	ballRigidBody->getMotionState()->getWorldTransform(trans);
	loc = trans.getOrigin();

	glPushMatrix();
	glTranslatef(loc[0], loc[1], loc[2]);
	glutWireSphere(1.0, 10, 10);
	glPopMatrix();

	boxRigidBody->getMotionState()->getWorldTransform(trans);
	loc = trans.getOrigin();
	mat = trans.getBasis();
	glMat[15] = 1;
	glMat[12] = loc[0];
	glMat[13] = loc[1];
	glMat[14] = loc[2];
	mat.getOpenGLSubMatrix(glMat);
	
	glPushMatrix();	
	glMultMatrixf(glMat);
	glutWireCube(2.0);
	glPopMatrix();

}


void CBulletWorld::release() {
	mWorld->removeRigidBody(ballRigidBody);
	delete ballRigidBody->getMotionState();
	delete ballRigidBody;

	mWorld->removeRigidBody(boxRigidBody);
	delete boxRigidBody->getMotionState();
	delete boxRigidBody;

	mWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete ballShape;

	delete groundShape;


	delete mWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void CBulletWorld::moveBall() {
	ballRigidBody->applyCentralImpulse( btVector3( 10.0, 0.0, 0.0) );
}