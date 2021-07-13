#pragma once

#include "math/Vector.hpp"

struct LerpComponent
{
	Vector3f destination;
	Vector3f start;
	float timeElapsed = 0.0f;
};