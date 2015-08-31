/*
Bullet Continuous Collision Detection and Physics Library
RagdollDemo
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

#ifndef RAGDOLLDEMO_H
#define RAGDOLLDEMO_H
#define CONSTRAINT_DEBUG_SIZE 0.2f

#include "GlutDemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "GlutStuff.h"
#include "GL_ShapeDrawer.h"
#include "LinearMath/btIDebugDraw.h"
#include "GLDebugDrawer.h"
#include <fstream>
#include <string>

class btBroadphaseInterface;
class btHingeConstraint;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

class RagdollDemo : public GlutDemoApplication
{
    
    virtual void renderme() {
        extern GLDebugDrawer gDebugDrawer;
        // Call the parent method.
        GlutDemoApplication::renderme();
        // Make a circle with a 0.9 radius at (0,0,0)
        // with RGB color (1,0,0).
        for (int i = 5; i<9; i++) {
            if(touches[i] == 1){
                gDebugDrawer.drawSphere(touchPoints[i], 0.2, btVector3(1., 0., 0.));
            }
        }
    }

	btAlignedObjectArray<class RagDoll*> m_ragdolls;

	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btBroadphaseInterface*	m_broadphase;

	btCollisionDispatcher*	m_dispatcher;

	btConstraintSolver*	m_solver;

	btDefaultCollisionConfiguration* m_collisionConfiguration;
    
    
    // spiderbot variables
    btRigidBody* body[9]; //one main body, 4x2 leg segments
    btCollisionShape* geom[9];
    bool pause;
    btHingeConstraint* joints[8];
    bool oneStep;
    int IDs[10];
public:
    int touches[10];
    btVector3 touchPoints[10];
    double weights[4][8];
    long timeStep;


public:
    btDynamicsWorld* m_ownerWorld;

	void initPhysics();
    

	void exitPhysics();
    
    void CreateBox(int index, double x, double y, double z, double length, double width, double height);
    
    void DeleteObject(int index);
    void CreateCylinder(int index, double x, double y, double z, double length, double xAngle, double yAngle, double zAngle, double radius);

	virtual ~RagdollDemo()
	{
		exitPhysics();
	}

	void spawnRagdoll(const btVector3& startOffset);

	virtual void clientMoveAndDisplay();

	virtual void displayCallback();

	virtual void keyboardCallback(unsigned char key, int x, int y);

	static DemoApplication* Create()
	{
		RagdollDemo* demo = new RagdollDemo();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
    btVector3 PointWorldToLocal(int index, btVector3 p) {
        btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
        return local1 * p;
    }
    
    btVector3 AxisWorldToLocal(int index, btVector3 a) {
        btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
        btVector3 zero(0,0,0);
        local1.setOrigin(zero); 
        return local1 * a; 
    }
    
    void CreateHinge(int index, btRigidBody& rbA, btRigidBody& rbB, btVector3& pivotInA, btVector3& pivotInB, btVector3& axisInA, btVector3& axisInB){
        
        btHingeConstraint* hingeC;

        hingeC =  new btHingeConstraint(rbA, rbB, pivotInA, pivotInB, axisInA, axisInB);
		joints[index] = hingeC;
        
		joints[index]->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);
    
        
        m_dynamicsWorld->addConstraint(joints[index], true);
        //set IDs equal to n
        for(int n = 0; n < 10; ++n){
            IDs[n] = n;
        }

    }
    
    btHingeConstraint DestroyHinge(int index){
			m_ownerWorld -> removeConstraint(joints[index]);
			delete joints[index]; joints[index] = 0;
    }
    
    void ActuateJoint(int jointIndex, double desiredAngle, double jointOffset, double timeStep){
        double currentAngle = joints[jointIndex] -> getHingeAngle();
        double diff = desiredAngle - currentAngle;


        joints[jointIndex] -> enableMotor(true);
        joints[jointIndex] -> setMaxMotorImpulse(5);
        joints[jointIndex] -> setMotorTarget(diff*3.14159/180.-jointOffset, timeStep);

    }
    void Save_Position(btRigidBody body){
        using namespace std;
        string outfilename = "/Users/mijitninja/Documents/bullet-2.82-r2704/Demos/RagdollDemo/fit.dat";
        
        btVector3 position(body.getCenterOfMassPosition());
        double Zcoord;
        Zcoord = position.getZ();
        ofstream outfile;
        cout << Zcoord;
        outfile.write(Zcoord);
        char ch = getchar();
        outfile.close()


    }

    
    
	
};


#endif
