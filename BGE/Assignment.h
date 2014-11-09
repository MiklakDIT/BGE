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
	void BuildPyramid(int pyr_size, glm::vec3 pyr_position, glm::vec3 block_size);

	shared_ptr<GameComponent> box;
};

