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
	BuildPyramid(5, glm::vec3(0, 1.5f, 0), glm::vec3(3.0f, 3.0f, 3.0f));
	BuildPyramid(14, glm::vec3(100, 1.5f, 100), glm::vec3(5.0f, 1.0f, 5.0f));
	BuildPyramid(7, glm::vec3(-100, 5, -100), glm::vec3(1.0f, 10.0f, 1.0f));
	BuildPyramid(3, glm::vec3(100, 5, -100), glm::vec3(1.0f, 5.0f, 5.0f));
	BuildPyramid(18, glm::vec3(-100, 0.25f, 100), glm::vec3(0.5f, 0.5f, 0.5f));

	return Game::Initialise();
}

void Assignment::AttachBlock(float x, float y, float z) {
	box = make_shared<Box>(block_size.x, block_size.y, block_size.z);
	box->transform->position = block_size * glm::vec3(x, y, z) + pyramid_position;
	Attach(box);
}

void Assignment::BuildPyramid(int pyr_size, glm::vec3 _pyramid_position, glm::vec3 _block_size) {
	pyramid_position = _pyramid_position;
	block_size = _block_size;

	// The pyramid will have pyr_size levels
	for (int i = 0; i < pyr_size; ++i) {
		for (int j = i; j < pyr_size; ++j) {

			// Add one edge
			AttachBlock(j - i / 2.0f, i, i / 2.0f);

			// The top level only has one block in it
			if (i < pyr_size - 1) {

				//Add the opposite edge
				AttachBlock(j - i / 2.0f, i, pyr_size - 1 - i / 2.0f);

				// Avoid adding the same corner twice
				if (j > i && j < pyr_size - 1) {

					// Add the remaining two edges.
					AttachBlock(i / 2.0f, i, j - i / 2.0f);
					AttachBlock(pyr_size - 1 - i / 2.0f, i, j - i / 2.0f);
				}
			}
		}
	}
}

void Assignment::Update() {
	Game::Update();
}