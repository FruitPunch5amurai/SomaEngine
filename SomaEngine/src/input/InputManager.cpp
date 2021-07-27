#include "somapch.hpp"
#include "input/InputManager.hpp"

namespace SOMA_ENGINE {
	InputManager::InputManager() : m_mouseCoords(0.0f)
	{
	}
	InputManager::~InputManager()
	{
	}
	void InputManager::Update()
	{
		for (auto& it : m_keyMap)
			m_previousKeyMap[it.first] = it.second;
	}
	void InputManager::KeyPress(uint32 keyId)
	{
		m_keyMap[keyId] = true;
	}
	void InputManager::KeyRelease(uint32 keyId)
	{
		m_keyMap[keyId] = false;
	}
	void InputManager::setMouseCoords(float x, float y)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}
	bool InputManager::isKeyDown(uint32 keyId) const
	{
		auto it = m_keyMap.find(keyId);
		if (it != m_keyMap.end())
		{
			return it->second;
		}
		return false;
	}
	bool InputManager::isKeyPressed(uint32 keyID) const
	{
		if (isKeyDown(keyID) && !WasKeyDown(keyID))
		{
			return true;
		}
		return false;
	}
	bool InputManager::WasKeyDown(uint32 keyID) const
	{
		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end())
		{
			return it->second;
		}
		return false;
	}
}