#pragma once
#include "GameComponent.h"

namespace BGE
{
	class Box :
		public GameComponent
	{
	public:
		Box(float width, float height, float depth);
		Box(glm::vec3 vec3);
		Box();
		~Box(void);
		bool Initialise();
		void Update();
	};
}
