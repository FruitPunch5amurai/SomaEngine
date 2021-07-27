#pragma once
#include "input/KeyCode.hpp"
#include "input/MouseCode.hpp"
#include <glm/glm.hpp>

namespace SOMA_ENGINE {

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