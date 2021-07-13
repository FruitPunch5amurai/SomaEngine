#pragma once
#include <core/common.hpp>

enum struct DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct SnakeBodyComponent
{
	entt::entity nextSnakeBody = entt::null;
	DIRECTION direction = DIRECTION::UP;
};
struct MovementControlComponent {

	InputControl* horizontal = nullptr;
	InputControl* vertical = nullptr;

};