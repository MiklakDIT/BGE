#include "Spider.h"

Spider::Spider():GameComponent(false)
{
	tag = "Spider";
}

Spider::~Spider()
{

}

void Spider::Update()
{
	timeElapsed += Time::deltaTime;
	Game::Instance()->PrintFloat("elapsed: ", timeElapsed);

	Game::Instance()->PrintVector("position: ", left_front_2->transform->position);

	if (timeElapsed < 1.0f) 
	{
		cephalothorax->rigidBody->setLinearVelocity(btVector3(0,0,0));
		abdomen->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		head->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_front_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_midfront_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_midrear_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_rear_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_front_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_midfront_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_midrear_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_rear_2->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_front_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_midfront_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_midrear_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		left_rear_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_front_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_midfront_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_midrear_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
		right_rear_1->rigidBody->setLinearVelocity(btVector3(0, 0, 0));
	}
	else
	{
		float sinus = sin(5 * timeElapsed);
		float cosinus = cos(5 * timeElapsed);
		//btVector3 speed = head->transform->orientation;
		float front_up = (sinus > 0.3 ? cosinus : 0.0f) * 1.7f;
		float rear_up = (sinus < -0.3 ? -cosinus : 0.0f) * 1.7f;
		float front_fwd = -(sinus > 0.3f && cosinus > 0.0f ? cosinus : 0.0f) * 1.5f;
		float rear_fwd = -(sinus < -0.3f && cosinus < 0.0f ? -cosinus : 0.0f) * 1.5f;

		glm::vec3 look = head->transform->right;

		glm::vec3 front = look  * glm::vec3(front_fwd, front_fwd, front_fwd) + glm::vec3(0, front_up, 0);
		btVector3 btFront = btVector3(front.x, front.y, front.z);
		glm::vec3 rear = look * glm::vec3(rear_fwd, rear_fwd, rear_fwd) + glm::vec3(0, rear_up, 0);
		btVector3 btRear = btVector3(rear.x, rear.y, rear.z);

		left_front_2->rigidBody->applyImpulse(btFront, btVector3());
		right_midfront_2->rigidBody->applyImpulse(btFront, btVector3());
		left_midrear_2->rigidBody->applyImpulse(btFront, btVector3());
		right_rear_2->rigidBody->applyImpulse(btFront, btVector3());

		left_midfront_2->rigidBody->applyImpulse(btRear, btVector3());
		right_front_2->rigidBody->applyImpulse(btRear, btVector3());
		left_rear_2->rigidBody->applyImpulse(btRear, btVector3());
		right_midrear_2->rigidBody->applyImpulse(btRear, btVector3());
	}
	GameComponent::Update();
}

bool Spider::Initialise()
{
	cephalothorax->rigidBody->setFriction(0.0f);
	abdomen->rigidBody->setFriction(0.0f);
	head->rigidBody->setFriction(0.0f);
	return GameComponent::Initialise();
}