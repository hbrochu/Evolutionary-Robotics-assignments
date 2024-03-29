/*
Bullet Continuous Collision Detection and Physics Library
Ragdoll Demo
Copyright (c) 2007 Starbreeze Studios

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Written by: Marten Svanfeldt
*/

#define CONSTRAINT_DEBUG_SIZE 0.2f


#include "btBulletDynamicsCommon.h"
#include "GlutStuff.h"
#include "GL_ShapeDrawer.h"
#include "LinearMath/btIDebugDraw.h"
#include "GLDebugDrawer.h"
#include "RagdollDemo.h"
#include <iostream>


// Enrico: Shouldn't these three variables be real constants and not defines?

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif
int i = 0;

class RagDoll
{
	enum
	{
		BODYPART_PELVIS = 0,
		BODYPART_SPINE,
		BODYPART_HEAD,

		BODYPART_LEFT_UPPER_LEG,
		BODYPART_LEFT_LOWER_LEG,

		BODYPART_RIGHT_UPPER_LEG,
		BODYPART_RIGHT_LOWER_LEG,

		BODYPART_LEFT_UPPER_ARM,
		BODYPART_LEFT_LOWER_ARM,

		BODYPART_RIGHT_UPPER_ARM,
		BODYPART_RIGHT_LOWER_ARM,

		BODYPART_COUNT
	};

	enum
	{
		JOINT_PELVIS_SPINE = 0,
		JOINT_SPINE_HEAD,

		JOINT_LEFT_HIP,
		JOINT_LEFT_KNEE,

		JOINT_RIGHT_HIP,
		JOINT_RIGHT_KNEE,

		JOINT_LEFT_SHOULDER,
		JOINT_LEFT_ELBOW,

		JOINT_RIGHT_SHOULDER,
		JOINT_RIGHT_ELBOW,

		JOINT_COUNT
	};

	btDynamicsWorld* m_ownerWorld;
	btCollisionShape* m_shapes[BODYPART_COUNT];
	btRigidBody* m_bodies[BODYPART_COUNT];
	btTypedConstraint* m_joints[JOINT_COUNT];

	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		m_ownerWorld->addRigidBody(body);

		return body;
	}

public:
    
    
    
    
    
	RagDoll (btDynamicsWorld* ownerWorld, const btVector3& positionOffset)
		: m_ownerWorld (ownerWorld)
	{
		// Setup the geometry
		m_shapes[BODYPART_PELVIS] = new btCapsuleShape(btScalar(0.15), btScalar(0.20));
		m_shapes[BODYPART_SPINE] = new btCapsuleShape(btScalar(0.15), btScalar(0.28));
		m_shapes[BODYPART_HEAD] = new btCapsuleShape(btScalar(0.40), btScalar(0.20));
		m_shapes[BODYPART_LEFT_UPPER_LEG] = new btCapsuleShape(btScalar(0.07), btScalar(0.45));
		m_shapes[BODYPART_LEFT_LOWER_LEG] = new btCapsuleShape(btScalar(0.05), btScalar(0.37));
		m_shapes[BODYPART_RIGHT_UPPER_LEG] = new btCapsuleShape(btScalar(0.07), btScalar(0.45));
		m_shapes[BODYPART_RIGHT_LOWER_LEG] = new btCapsuleShape(btScalar(0.05), btScalar(0.37));
		m_shapes[BODYPART_LEFT_UPPER_ARM] = new btCapsuleShape(btScalar(0.05), btScalar(0.33));
		m_shapes[BODYPART_LEFT_LOWER_ARM] = new btCapsuleShape(btScalar(0.04), btScalar(0.25));
		m_shapes[BODYPART_RIGHT_UPPER_ARM] = new btCapsuleShape(btScalar(0.05), btScalar(0.33));
		m_shapes[BODYPART_RIGHT_LOWER_ARM] = new btCapsuleShape(btScalar(0.04), btScalar(0.25));

		// Setup all the rigid bodies
		btTransform offset; offset.setIdentity();
		offset.setOrigin(positionOffset);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
		m_bodies[BODYPART_PELVIS] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_PELVIS]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
		m_bodies[BODYPART_SPINE] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_SPINE]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.6), btScalar(0.)));
		m_bodies[BODYPART_HEAD] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_HEAD]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.65), btScalar(0.)));
		m_bodies[BODYPART_LEFT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_LEG]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.2), btScalar(0.)));
		m_bodies[BODYPART_LEFT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_LEG]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.65), btScalar(0.)));
		m_bodies[BODYPART_RIGHT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_LEG]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.2), btScalar(0.)));
		m_bodies[BODYPART_RIGHT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_LEG]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.35), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,M_PI_2);
		m_bodies[BODYPART_LEFT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_ARM]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.7), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,M_PI_2);
		m_bodies[BODYPART_LEFT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_ARM]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.35), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,-M_PI_2);
		m_bodies[BODYPART_RIGHT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_ARM]);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.7), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,-M_PI_2);
		m_bodies[BODYPART_RIGHT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_ARM]);

		// Setup some damping on the m_bodies
		for (int i = 0; i < BODYPART_COUNT; ++i)
		{
			m_bodies[i]->setDamping(0.05, 0.85);
			m_bodies[i]->setDeactivationTime(0.8);
			m_bodies[i]->setSleepingThresholds(1.6, 2.5);
		}

		// Now setup the constraints
		btHingeConstraint* hingeC;
		btConeTwistConstraint* coneC;

		btTransform localA, localB;

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.15), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_SPINE], localA, localB);
		hingeC->setLimit(btScalar(-M_PI_4), btScalar(M_PI_2));
		m_joints[JOINT_PELVIS_SPINE] = hingeC;
		hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_PELVIS_SPINE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI_2); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.30), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_HEAD], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, M_PI_2);
		m_joints[JOINT_SPINE_HEAD] = coneC;
		coneC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_SPINE_HEAD], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,-M_PI_4*5); localA.setOrigin(btVector3(btScalar(-0.18), btScalar(-0.10), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,-M_PI_4*5); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_LEFT_UPPER_LEG], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, 0);
		m_joints[JOINT_LEFT_HIP] = coneC;
		coneC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_HIP], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_LEG], *m_bodies[BODYPART_LEFT_LOWER_LEG], localA, localB);
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_LEFT_KNEE] = hingeC;
		hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_KNEE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI_4); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,M_PI_4); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_RIGHT_UPPER_LEG], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, 0);
		m_joints[JOINT_RIGHT_HIP] = coneC;
		coneC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_HIP], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_LEG], *m_bodies[BODYPART_RIGHT_LOWER_LEG], localA, localB);
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_RIGHT_KNEE] = hingeC;
		hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_KNEE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI); localA.setOrigin(btVector3(btScalar(-0.2), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_LEFT_UPPER_ARM], localA, localB);
		coneC->setLimit(M_PI_2, M_PI_2, 0);
		coneC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_joints[JOINT_LEFT_SHOULDER] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_SHOULDER], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_ARM], *m_bodies[BODYPART_LEFT_LOWER_ARM], localA, localB);
//		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_LEFT_ELBOW] = hingeC;
		hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_ELBOW], true);



		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,0); localA.setOrigin(btVector3(btScalar(0.2), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_RIGHT_UPPER_ARM], localA, localB);
		coneC->setLimit(M_PI_2, M_PI_2, 0);
		m_joints[JOINT_RIGHT_SHOULDER] = coneC;
		coneC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_SHOULDER], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_ARM], *m_bodies[BODYPART_RIGHT_LOWER_ARM], localA, localB);
//		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_RIGHT_ELBOW] = hingeC;
		hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_ELBOW], true);
	}

	virtual	~RagDoll ()
	{
		int i;

		// Remove all constraints
		for ( i = 0; i < JOINT_COUNT; ++i)
		{
			m_ownerWorld->removeConstraint(m_joints[i]);
			delete m_joints[i]; m_joints[i] = 0;
		}

		// Remove all bodies and shapes
		for ( i = 0; i < BODYPART_COUNT; ++i)
		{
			m_ownerWorld->removeRigidBody(m_bodies[i]);
			
			delete m_bodies[i]->getMotionState();

			delete m_bodies[i]; m_bodies[i] = 0;
			delete m_shapes[i]; m_shapes[i] = 0;
		}
	}
};
static RagdollDemo* ragdollDemo;

bool Contact(btManifoldPoint& cp,
                           void* body0, void* body1){//determines if sensor is touching the ground
    int *ID1, *ID2;
    btCollisionObject* o1 = static_cast<btCollisionObject*>(body0);
    btCollisionObject* o2 = static_cast<btCollisionObject*>(body1);
    int groundID = 9;
    ID1 = static_cast<int*>(o1->getUserPointer());
    ID2 = static_cast<int*>(o2->getUserPointer());
    /* Your code will go here. See the next step. */
    printf("ID1 = %d, ID2 = %d \n", *ID1, *ID2);
    ragdollDemo -> touches[*ID1] = 1;
    ragdollDemo -> touches[*ID2] = 1;
    ragdollDemo->touchPoints[*ID1] = cp.m_positionWorldOnB;
    ragdollDemo->touchPoints[*ID2] = cp.m_positionWorldOnB;

    return false;
}


void RagdollDemo::initPhysics()
{
    
    gContactProcessedCallback = Contact;
    ragdollDemo = this;
	// Setup the basic world

	setTexturing(true);
	setShadows(true);

	setCameraDistance(btScalar(5.));

	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);

	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	//m_dynamicsWorld->getDispatchInfo().m_useConvexConservativeDistanceUtil = true;
	//m_dynamicsWorld->getDispatchInfo().m_convexConservativeDistanceThreshold = 0.01f;



	// Setup a big ground box
	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.),btScalar(10.),btScalar(200.)));
		m_collisionShapes.push_back(groundShape);
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0,-10,0));

#define CREATE_GROUND_COLLISION_OBJECT 1
#ifdef CREATE_GROUND_COLLISION_OBJECT
		btCollisionObject* fixedGround = new btCollisionObject();
		fixedGround->setCollisionShape(groundShape);
		fixedGround->setWorldTransform(groundTransform);
		m_dynamicsWorld->addCollisionObject(fixedGround);
#else
		localCreateRigidBody(btScalar(0.),groundTransform,groundShape);
#endif //CREATE_GROUND_COLLISION_OBJECT
        fixedGround ->setUserPointer(&IDs[9]);

	}

	// Spawn one ragdoll
	//btVector3 startOffset(1,0.5,0);
	//spawnRagdoll(startOffset);
	//startOffset.setValue(-1,0.5,0);
	//spawnRagdoll(startOffset);
    
    CreateBox(0, 0.0, 2.0, 0.0, 1.0, 0.2, 1.0);
    CreateCylinder(1,  2.0, 2.0,  0.0, 1.0, M_PI_2, 0.0, 0.0, 0.1);
    CreateCylinder(2, -2.0, 2.0,  0.0, 1.0, M_PI_2, 0.0, M_PI, 0.1);
    CreateCylinder(3,  0.0, 2.0,  2.0, 1.0, 0.0, M_PI, M_PI_2,0.1 );
	CreateCylinder(4,  0.0, 2.0, -2.0, 1.0, 0.0, 0.0, M_PI_2,0.1 );
	CreateCylinder(5,  3.0, 1.0,  0.0, 1.0, 0.0, 0.0, 0.0,0.1);
	CreateCylinder(6, -3.0, 1.0,  0.0, 1.0, 0.0, 0.0, 0.0,0.1);
	CreateCylinder(7,  0.0, 1.0,  3.0, 1.0, 0.0, 0.0, 0.0,0.1);
	CreateCylinder(8,  0.0, 1.0, -3.0, 1.0, 0.0, 0.0, 0.0,0.1);
    
    //add constraints
    btVector3 localCenter = PointWorldToLocal(0, btVector3(0.,2.,0.));
    btVector3 localAxis = AxisWorldToLocal(0, btVector3(0.,2.,0.));

    //forward left limb
    btVector3 localCenterLeftFront = PointWorldToLocal(1, btVector3(btScalar(3.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLeftFront = AxisWorldToLocal(1, btVector3(btScalar(0.),btScalar(0.),btScalar(-1.)));
    btVector3 localCenterLowerLeftFront = PointWorldToLocal(5, btVector3(btScalar(3.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLowerLeftFront = AxisWorldToLocal(5, btVector3(btScalar(0.),btScalar(0.),btScalar(-1.)));
    
    CreateHinge(0, *body[5], *body[1], localCenterLowerLeftFront, localCenterLeftFront, localAxisLowerLeftFront, localAxisLeftFront);
    
    //front left hip
    btVector3 localCenterLFHFront = PointWorldToLocal(0, btVector3(btScalar(1.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLFHFront = AxisWorldToLocal(0, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    btVector3 localCenterLowerLFHFront = PointWorldToLocal(1, btVector3(btScalar(1.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLowerLFHFront = AxisWorldToLocal(1, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    
    CreateHinge(4, *body[0], *body[1], localCenterLFHFront, localCenterLowerLFHFront, localAxisLFHFront, localAxisLowerLFHFront);
    
    //right back
    btVector3 localCenterRBFront = PointWorldToLocal(2, btVector3(btScalar(-3.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisRBFront = AxisWorldToLocal(2, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    btVector3 localCenterLowerRBFront = PointWorldToLocal(6, btVector3(btScalar(-3.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLowerRBFront = AxisWorldToLocal(6, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    
    CreateHinge(1, *body[6], *body[2], localCenterLowerRBFront, localCenterRBFront, localAxisLowerRBFront, localAxisRBFront);
    
    //right back hip
    btVector3 localCenterRBHFront = PointWorldToLocal(0, btVector3(btScalar(-1.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisRBHFront = AxisWorldToLocal(0, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    btVector3 localCenterLowerRBHFront = PointWorldToLocal(2, btVector3(btScalar(-1.),btScalar(2.),btScalar(0.)));
    btVector3 localAxisLowerRBHFront = AxisWorldToLocal(2, btVector3(btScalar(0.),btScalar(0.),btScalar(1.)));
    
    CreateHinge(5, *body[2], *body[0], localCenterLowerRBHFront, localCenterRBHFront, localAxisLowerRBHFront, localAxisRBHFront);
    
    //left back
    btVector3 localCenterLBFront = PointWorldToLocal(3, btVector3(btScalar(0.),btScalar(2.),btScalar(3.)));
    btVector3 localAxisLBFront = AxisWorldToLocal(3, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    btVector3 localCenterLowerLBFront = PointWorldToLocal(7, btVector3(btScalar(0.),btScalar(2.),btScalar(3.)));
    btVector3 localAxisLowerLBFront = AxisWorldToLocal(7 , btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    
    CreateHinge(2, *body[7], *body[3], localCenterLowerLBFront, localCenterLBFront, localAxisLowerLBFront, localAxisLBFront);
    
    //left back hip
    btVector3 localCenterLBHFront = PointWorldToLocal(0, btVector3(btScalar(0.),btScalar(2.),btScalar(1.)));
    btVector3 localAxisLBHFront = AxisWorldToLocal(0, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    btVector3 localCenterLowerLBHFront = PointWorldToLocal(3, btVector3(btScalar(0.),btScalar(2.),btScalar(1.)));
    btVector3 localAxisLowerLBHFront = AxisWorldToLocal(3, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    
    CreateHinge(6, *body[3], *body[0], localCenterLowerLBHFront, localCenterLBHFront, localAxisLowerLBHFront, localAxisLBHFront);
    
    //forward right
    btVector3 localCenterRFFront = PointWorldToLocal(4, btVector3(btScalar(0.),btScalar(2.),btScalar(-3.)));
    btVector3 localAxisRFFront = AxisWorldToLocal(4, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    btVector3 localCenterLowerRFFront = PointWorldToLocal(8, btVector3(btScalar(0.),btScalar(2.),btScalar(-3.)));
    btVector3 localAxisLowerRFFront = AxisWorldToLocal(8, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    
    CreateHinge(3, *body[4], *body[8], localCenterRFFront, localCenterLowerRFFront, localAxisRFFront, localAxisLowerRFFront);
    
    //forward right hip
    btVector3 localCenterRFHFront = PointWorldToLocal(0, btVector3(btScalar(0.),btScalar(2.),btScalar(-1.)));
    btVector3 localAxisRFHFront = AxisWorldToLocal(0, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    btVector3 localCenterLowerRFHFront = PointWorldToLocal(4, btVector3(btScalar(0.),btScalar(2.),btScalar(-1.)));
    btVector3 localAxisLowerRFHFront = AxisWorldToLocal(4, btVector3(btScalar(1.),btScalar(0.),btScalar(0.)));
    
    CreateHinge(7, *body[0], *body[4], localCenterRFHFront, localCenterLowerRFHFront, localAxisRFHFront, localAxisLowerRFHFront);
    
    //set offset and limits
    
    double offset = -M_PI_2;
    for (int i = 0; i < 4; ++i)
        joints[i]->setLimit(-M_PI_4 - offset, M_PI_4 - offset);
    
    offset = M_PI_2;
    for (int i = 4; i < 8; ++i)
        joints[i]->setLimit(-M_PI_4 - offset, M_PI_4 - offset);
    clientResetScene();
}
void RagdollDemo::DeleteObject(int index)
{
    btRigidBody* rb = body[index];
    btCollisionShape* cs = geom[index];
    delete rb;
    delete cs;
}



void RagdollDemo::spawnRagdoll(const btVector3& startOffset)
{
	RagDoll* ragDoll = new RagDoll (m_dynamicsWorld, startOffset);
	m_ragdolls.push_back(ragDoll);
}	

void RagdollDemo::clientMoveAndDisplay()
{

    
    //counter
    i++;
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTimeMicroseconds();

	float minFPS = 100000.f/60.f;
	if (ms > minFPS)
		ms = minFPS;

	if (!pause)
	{
        for (int n = 0; n<10; n++) {
            touches[n] = 0;
        }
        m_dynamicsWorld->stepSimulation(ms / 100000.f);

        //optional but useful: debug drawing
        m_dynamicsWorld->debugDrawWorld();
        
	}
    if(oneStep){
        m_dynamicsWorld->stepSimulation(ms / 1.f);
        oneStep = false;
    }
    if ((!pause || (pause && oneStep)) && (1 == i%50)) {
        for(int c =0; c<4; c++){
            double random = (rand()/45)*90.-45.;
            double negRandom = (rand()/-45)*90.-45.;
            double angle = 0;
            if(rand() == 0){
                angle = random;
            }
            else{
                angle = negRandom;
            }
            ActuateJoint(c, angle, 90., ms / 1000000.f);
        }


        for(int c =4; c<8; c++){
            double random = (rand()/45)*90.-45.;
            double negRandom = (rand()/-45)*90.-45.;
            double angle = random - negRandom;
            ActuateJoint(c, angle, 90., ms / 1000000.f);
        }


        m_dynamicsWorld->stepSimulation(ms / 100000.f);
        oneStep = false;

    }
    using namespace std;
    for (int c = 0; c<10; ++c){
        cout << touches[c];
    }
    cout << "\n";



	renderme();

	glFlush();

	glutSwapBuffers();
}

void RagdollDemo::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	renderme();

	//optional but useful: debug drawing
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

	glFlush();
	glutSwapBuffers();
}

void RagdollDemo::keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
		{
		btVector3 startOffset(0,2,0);
		spawnRagdoll(startOffset);
		break;
		}
    case 'p':
        {
            pause = !pause;
            break;
        }
    case 'o':
        {
            oneStep = !oneStep;
            break;
        }
	default:
		DemoApplication::keyboardCallback(key, x, y);
	}

	
}



void	RagdollDemo::exitPhysics()
{

	int i;
    DeleteObject(0);
	for (i=0;i<m_ragdolls.size();i++)
	{
		RagDoll* doll = m_ragdolls[i];
		delete doll;
	}

	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}

	//delete dynamics world
	delete m_dynamicsWorld;

	//delete solver
	delete m_solver;

	//delete broadphase
	delete m_broadphase;

	//delete dispatcher
	delete m_dispatcher;

	delete m_collisionConfiguration;

	
}
void RagdollDemo::CreateBox(int index, double x, double y, double z, double length, double width, double height){

    geom[index] = new btBoxShape(btVector3(btScalar(length),btScalar(width),btScalar(height)));
    
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(btVector3(btScalar(x),btScalar(y),btScalar(z)));
    
    
    body[index] = localCreateRigidBody(btScalar(1.0), offset, geom[index]);
    body[index]->setUserPointer(&IDs[index]);
    
    
    
}
void RagdollDemo::CreateCylinder(int index, double x, double y, double z, double length, double xAngle, double yAngle, double zAngle, double radius){
    
    geom[index] = new btCylinderShape(btVector3(2 * radius, length, 0.0));
    
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(btVector3(btScalar(x), btScalar(y), btScalar(z)));
    offset.getBasis().setEulerZYX(zAngle, yAngle, xAngle);
    
    body[index] = localCreateRigidBody(btScalar(1.0), offset, geom[index]);
    body[index]->setUserPointer(&IDs[index]);
    
}




