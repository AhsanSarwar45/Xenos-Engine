#pragma once

#include <glm/glm.hpp>
#include "Xenos/Input/KeyCodes.h"
#include "Xenos/Input/MouseCodes.h"

namespace Xenos
{

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		
	};
}