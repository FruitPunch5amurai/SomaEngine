#pragma once

#include "math/math.hpp"
class InputControl {
public:
	InputControl();
	void AddAmt(float amtToAdd);
	float GetAmt();
private :
	float amount;
};

inline InputControl::InputControl() :
	amount(0.0f) {}

inline void InputControl::AddAmt(float amtToAdd)
{
	amount += amtToAdd;
}
inline float InputControl::GetAmt()
{
	return Math::clamp(amount, -1.0f, 1.0f);
}