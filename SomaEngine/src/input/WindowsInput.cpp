#include "somapch.hpp"
#include "core/Input.hpp"
#include "core/game/IMainGame.hpp"
#include "platform/sdl/SDLWindow.hpp"

namespace SOMA_ENGINE {
	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<SDLWindow*>(IMainGame::Get().window);
		return window->IsKeyPressed(key);
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<SDLWindow*>(IMainGame::Get().window);
		return window->IsKeyPressed(button);
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<SDLWindow*>(IMainGame::Get().window);
		return window->GetMousePosition();
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}