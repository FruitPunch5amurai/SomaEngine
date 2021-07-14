#pragma once

#include "core/common.hpp"
namespace SOMA_ENGINE {

	using MouseCode = uint16_t;

	namespace Mouse
	{
#ifdef SOMA_PLATFORM_SDL
		enum : MouseCode
		{
			MOUSE_LEFT_BUTTON = 0,
			MOUSE_MIDDLE_BUTTON = 1,
			MOUSE_RIGHT_BUTTON = 2,
			MOUSE_WHEEL_UP = 3,
			MOUSE_WHEEL_DOWN = 4
		};
#endif
	}

}