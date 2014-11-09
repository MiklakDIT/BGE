#pragma once
#include "Game.h"
#include "Box.h"
#include "GameComponent.h"

using namespace BGE;

class Assignment :
	public Game
{
public:
	Assignment();
	~Assignment();
	bool Initialise();
	void Update();
	void AttachBlock(float x, float y, float z);
	void BuildPyramid(int pyr_size, glm::vec3 _pyramid_position, glm::vec3 _block_size);
	glm::vec3 pyramid_position, block_size;

	shared_ptr<GameComponent> box;
};

