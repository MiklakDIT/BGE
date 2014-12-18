#include "SpiderFactory.h"


SpiderFactory::SpiderFactory(btDiscreteDynamicsWorld * dynamicsWorld)
{
	this->dynamicsWorld = dynamicsWorld;
}


SpiderFactory::~SpiderFactory()
{
}

shared_ptr<PhysicsController> SpiderFactory::CreateCapsule(float radius, float height, glm::vec3 pos, glm::vec3 color, float mass, glm::quat quat)
{
	
	btCollisionShape* capsuleShape = new btCapsuleShape(radius, height);
	btVector3 inertia(0, 0, 0);
	capsuleShape->calculateLocalInertia(mass, inertia);

	// This is a container for the box model
	shared_ptr<GameComponent> cap = make_shared<Capsule>(radius, height);
	cap->Initialise();
	cap->transform->position = pos;
	cap->transform->diffuse = color;
	Game::Instance()->Attach(cap);

	// Create the rigid body
	btDefaultMotionState * motionState = new btDefaultMotionState(btTransform(GLToBtQuat(quat)
		, GLToBtVector(pos)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, capsuleShape, inertia);
	btRigidBody * body = new btRigidBody(rigidBodyCI);
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	body->setFriction(0.2f);
	dynamicsWorld->addRigidBody(body);

	// Create the physics component and add it to the box
	shared_ptr<PhysicsController> component = make_shared<PhysicsController>(capsuleShape, body, motionState);
	body->setUserPointer(component.get());
	component->tag = "capsule";
	cap->Attach(component);

	return component;
}

void SpiderFactory::CreateBody()
{
	spider->cephalothorax = CreateCapsule(4, 1, glm::vec3(position.x, position.y, position.z), glm::vec3(.1, .0, .0), .5);
	spider->abdomen = CreateCapsule(4, 1, glm::vec3(position.x + 8, position.y, position.z), glm::vec3(.0, .2, .2), .5);
	spider->head = CreateCapsule(1, 0.5, glm::vec3(position.x - 5, position.y + 6, position.z), glm::vec3(.1, .1, .1), .5);

	btHingeConstraint* abdomen_cephalothorax;
	localA.setIdentity(); localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI); localA.setOrigin(btVector3(-4.5, 0, 0));
	localB.getBasis().setEulerZYX(0, 0, M_PI); localB.setOrigin(btVector3(4.5, 0, 0));
	abdomen_cephalothorax = new btHingeConstraint(*spider->abdomen->rigidBody, *spider->cephalothorax->rigidBody, localA, localB);
	abdomen_cephalothorax->setLimit(-0.5, 0.5);
	dynamicsWorld->addConstraint(abdomen_cephalothorax);

	btFixedConstraint* head_cephalothorax;
	localA.setIdentity(); localB.setIdentity();
	localA.setOrigin(btVector3(1.5, -0.5, 0));
	localB.setOrigin(btVector3(-4.5, 0, 0));
	head_cephalothorax = new btFixedConstraint(*spider->head->rigidBody, *spider->cephalothorax->rigidBody, localA, localB);
	dynamicsWorld->addConstraint(head_cephalothorax);
}

void SpiderFactory::CreateLegs() 
{
	float radius = 0.25f;
	float height = SQRT2;
	float x = 10.5f;
	float m_x = 4.5f;
	float y = position.y + height;
	float z = 6.0f;
	float m_z = 10.5f;

	spider->left_front_1 = CreateCapsule(radius, height, glm::vec3(position.x - x, y, position.z + z));
	spider->right_front_1 = CreateCapsule(radius, height, glm::vec3(position.x - x, y, position.z - z));
	spider->left_midfront_1 = CreateCapsule(radius, height, glm::vec3(position.x - m_x, y, position.z + m_z));
	spider->right_midfront_1 = CreateCapsule(radius, height, glm::vec3(position.x - m_x, y, position.z - m_z));
	spider->left_midrear_1 = CreateCapsule(radius, height, glm::vec3(position.x + m_x, y, position.z + m_z));
	spider->right_midrear_1 = CreateCapsule(radius, height, glm::vec3(position.x + m_x, y, position.z - m_z));
	spider->left_rear_1 = CreateCapsule(radius, height, glm::vec3(position.x + x, y, position.z + z));
	spider->right_rear_1 = CreateCapsule(radius, height, glm::vec3(position.x + x, y, position.z - z));

	height *= 2;

	spider->left_front_2 = CreateCapsule(radius, height, glm::vec3(position.x - x, y, position.z + z));
	spider->right_front_2 = CreateCapsule(radius, height, glm::vec3(position.x - x, y, position.z - z));
	spider->left_midfront_2 = CreateCapsule(radius, height, glm::vec3(position.x - m_x, y, position.z + m_z));
	spider->right_midfront_2 = CreateCapsule(radius, height, glm::vec3(position.x - m_x, y, position.z - m_z));
	spider->left_midrear_2 = CreateCapsule(radius, height, glm::vec3(position.x + m_x, y, position.z + m_z));
	spider->right_midrear_2 = CreateCapsule(radius, height, glm::vec3(position.x + m_x, y, position.z - m_z));
	spider->left_rear_2 = CreateCapsule(radius, height, glm::vec3(position.x + x, y, position.z + z));
	spider->right_rear_2 = CreateCapsule(radius, height, glm::vec3(position.x + x, y, position.z - z));
}

void SpiderFactory::ConnectLegsToBody()
{
	float euler_x = M_PI / 1.25f;
	float front_euler_z = M_PI / 3.0f;
	float rear_euler_z = -M_PI / 6.0f;
	float midfront_euler_z = M_PI / 12.0f;
	float midrear_euler_z = -M_PI / 12.0f;
	float origin_front = -3.5f;
	float origin_midfront = -1.5f;
	float origin_left = 2.0f;
	float origin_midleft = 3.5f;
	float cephalothorax_limit = M_PI / 6.0f;

	localA.getBasis().setEulerZYX(0, 0, 0);
	localB.setOrigin(btVector3(0, 2 * SQRT2, 0));

	ConnectLegToBody(spider->left_front_1, origin_front, origin_left, euler_x, front_euler_z);
	ConnectLegToBody(spider->right_front_1, origin_front, -origin_left, -euler_x, front_euler_z);
	ConnectLegToBody(spider->left_rear_1, -origin_front, origin_left, euler_x, rear_euler_z);
	ConnectLegToBody(spider->right_rear_1, -origin_front, -origin_left, -euler_x, rear_euler_z);
	ConnectLegToBody(spider->left_midfront_1, origin_midfront, origin_midleft, euler_x, midfront_euler_z);
	ConnectLegToBody(spider->right_midfront_1, origin_midfront, -origin_midleft, -euler_x, midfront_euler_z);
	ConnectLegToBody(spider->left_midrear_1, -origin_midfront, origin_midleft, euler_x, midrear_euler_z);
	ConnectLegToBody(spider->right_midrear_1, -origin_midfront, -origin_midleft, -euler_x, midrear_euler_z);
}

void SpiderFactory::ConnectLegToBody(shared_ptr<PhysicsController> leg, float origin_x, float origin_z, float euler_x, float euler_z)
{
	localA.setOrigin(btVector3(origin_x, -1.0f, origin_z));
	localB.getBasis().setEulerZYX(euler_x, 0, euler_z);
	btConeTwistConstraint* leg_to_body;
	leg_to_body = new btConeTwistConstraint(*spider->cephalothorax->rigidBody, *leg->rigidBody, localA, localB);
	leg_to_body->setLimit(0, 0, M_PI / 5.0f);
	dynamicsWorld->addConstraint(leg_to_body);
}

void SpiderFactory::ConnectLegHinges()
{
	float front_euler_z = M_PI / 4.5f;
	float rear_euler_z = -M_PI / 6.0f;
	float midfront_euler_z = M_PI / 12.0f;
	float midrear_euler_z = -M_PI / 12.0f;
	float euler_y = M_PI / 2.0f;
	float euler_z = M_PI / 3.0f;

	localA.setOrigin(btVector3(0, -2 * SQRT2 - 0.5, 0));
	localB.setOrigin(btVector3(0, 4 * SQRT2 + 0.5, 0));
	
	ConnectLegHinge(spider->left_front_1, spider->left_front_2, euler_y, front_euler_z);
	ConnectLegHinge(spider->left_midfront_1, spider->left_midfront_2, euler_y, midfront_euler_z);
	ConnectLegHinge(spider->left_midrear_1, spider->left_midrear_2, euler_y, midrear_euler_z);
	ConnectLegHinge(spider->left_rear_1, spider->left_rear_2, euler_y, rear_euler_z);
	ConnectLegHinge(spider->right_front_1, spider->right_front_2, -euler_y, front_euler_z);
	ConnectLegHinge(spider->right_midfront_1, spider->right_midfront_2, -euler_y, midfront_euler_z);
	ConnectLegHinge(spider->right_midrear_1, spider->right_midrear_2, -euler_y, midrear_euler_z);
	ConnectLegHinge(spider->right_rear_1, spider->right_rear_2, -euler_y, rear_euler_z);
}

void SpiderFactory::ConnectLegHinge(shared_ptr<PhysicsController> leg1, shared_ptr<PhysicsController> leg2, float euler_y, float euler_z)
{
	localA.getBasis().setEulerZYX(0, euler_y, euler_z);
	localB.getBasis().setEulerZYX(0, euler_y, euler_z);
	btHingeConstraint* leg_hinge;
	leg_hinge = new btHingeConstraint(*leg1->rigidBody, *leg2 ->rigidBody, localA, localB);
	leg_hinge->setLimit(-M_PI / 2, -M_PI / 3);
	dynamicsWorld->addConstraint(leg_hinge);
}

shared_ptr<Spider> SpiderFactory::CreateSpider(glm::vec3 position)
{
	spider = make_shared<Spider>();
	this->position = position;
	CreateLegs();
	CreateBody();
	ConnectLegsToBody();
	ConnectLegHinges();
	Game::Instance()->Attach(spider);
	return spider;
}
