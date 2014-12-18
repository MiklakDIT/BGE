#pragma once
#include "GameComponent.h"
#include "PhysicsController.h"
#include "Game.h"
#include "Utils.h"

using namespace BGE;

class Spider
	: public GameComponent
{
public:
	Spider();
	~Spider();

	shared_ptr<PhysicsController> cephalothorax, abdomen, head;
	shared_ptr<PhysicsController> left_front_1, right_front_1, left_midfront_1, right_midfront_1, left_midrear_1, right_midrear_1, left_rear_1, right_rear_1;
	shared_ptr<PhysicsController> left_front_2, right_front_2, left_midfront_2, right_midfront_2, left_midrear_2, right_midrear_2, left_rear_2, right_rear_2;
	
	void Update();
	bool Initialise();

private:
	float timeElapsed;
};

