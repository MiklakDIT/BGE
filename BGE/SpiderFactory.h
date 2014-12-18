#pragma once
#include "GameComponent.h"
#include "PhysicsController.h"
#include "Utils.h"
#include "Game.h"
#include "Capsule.h"
#include "Spider.h"

#define SQRT2 1.414213562373095

using namespace BGE;

class SpiderFactory
{
public:
	SpiderFactory(btDiscreteDynamicsWorld * );
	~SpiderFactory();
	shared_ptr<Spider> CreateSpider(glm::vec3 position);
	shared_ptr<Spider> spider;

private:
	shared_ptr<PhysicsController> CreateCapsule(float radius, float height, glm::vec3 pos, glm::vec3 color = glm::vec3(0, 0, 0), float mass = 1.0f, glm::quat quat = glm::quat());
	void CreateBody();
	void CreateLegs();
	void ConnectLegsToBody();
	void ConnectLegToBody(shared_ptr<PhysicsController> leg, float origin_x, float origin_z, float euler_x, float euler_z);
	void ConnectLegHinges();
	void ConnectLegHinge(shared_ptr<PhysicsController> leg1, shared_ptr<PhysicsController> leg2, float euler_y, float euler_z);
	btDiscreteDynamicsWorld * dynamicsWorld;
	btTransform localA, localB;
	glm::vec3 position;
};

