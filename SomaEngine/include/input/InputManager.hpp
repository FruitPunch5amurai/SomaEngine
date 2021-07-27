#pragma once
#include "dataStructures/map.hpp"
#include "core/common.hpp"
#include <glm/glm.hpp>

namespace SOMA_ENGINE {
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void Update();

		void KeyPress(uint32 keyId);
		void KeyRelease(uint32 keyId);
		void setMouseCoords(float x, float y);
		bool isKeyDown(uint32 keyId) const;
		bool isKeyPressed(uint32 keyID) const;
		glm::vec2 getMouseCoords() const { return m_mouseCoords; };

	private:
		bool WasKeyDown(uint32 keyID) const;
		Map<uint32, bool> m_keyMap;
		Map<uint32, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;

	};
}