#include "Assignment.h"
using namespace BGE;

Assignment::Assignment()
{
}


Assignment::~Assignment()
{
}


bool Assignment::Initialise()
{
	SetGround(make_shared<Ground>());

	BuildPyramid(8, glm::vec3(0, 2.0f, 0), glm::vec3(4.0f, 4.0f, 4.0f));
	BuildPyramid(18, glm::vec3(100, 1.5f, 100), glm::vec3(5.0f, 1.0f, 5.0f));
	BuildPyramid(10, glm::vec3(-100, 5, -100), glm::vec3(1.0f, 10.0f, 1.0f));
	BuildPyramid(5, glm::vec3(100, 5, -100), glm::vec3(1.0f, 5.0f, 5.0f));
	BuildPyramid(50, glm::vec3(-100, 0.25f, 100), glm::vec3(0.5f, 0.5f, 0.5f));

	return Game::Initialise();
}

void Assignment::BuildPyramid(int pyr_size, glm::vec3 pyr_position, glm::vec3 block_size) {
	// The pyramid will have pyr_size levels
	for (int i = 0; i < pyr_size; ++i) {
		box = make_shared<Box>(block_size * glm::vec3(pyr_size - i, 1, pyr_size - i));
		box->transform->position = block_size * glm::vec3(0.0f, i, 0.0f) + pyr_position;
		Attach(box);
	}
}

void Assignment::Update() {
	Game::Update();
}