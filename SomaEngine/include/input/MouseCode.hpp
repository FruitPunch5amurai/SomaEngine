#pragma once

#include "core/common.hpp"
namespace SOMA_ENGINE {
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			MOUSE_LEFT_BUTTON = 1,
			MOUSE_MIDDLE_BUTTON = 2,
			MOUSE_RIGHT_BUTTON = 3,
			MOUSE_WHEEL_UP = 4,
			MOUSE_WHEEL_DOWN = 5
		};
	}
}