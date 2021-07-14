#include "somapch.hpp"

#include "InputHandler.hpp"
#include "input/input.hpp"
#define MOUSE_OFFSET Input::NUM_KEYS

void InputHandler::onKeyDown(uint32 keyCode, bool isRepeat)
{
	updateInput(keyCode, 1.0f, isRepeat);
}

void InputHandler::onKeyUp(uint32 keyCode, bool isRepeat)
{
	updateInput(keyCode, -1.0f, isRepeat);
}

void InputHandler::onMouseDown(uint32 mouseButton, uint8 numClicks)
{
	updateInput(mouseButton + MOUSE_OFFSET, 1.0f,false);
}

void InputHandler::onMouseUp(uint32 mouseButton, uint8 numClicks)
{
	updateInput(mouseButton + MOUSE_OFFSET, -1.0f, false);
}

void InputHandler::onMouseMove(uint32 mousePosX, uint32 mousePosY, uint32 deltaX, uint32 deltaY)
{
}

void InputHandler::addKeyControl(uint32 keyCode, InputControl& inputControl, float weight)
{
	m_inputs[keyCode].push_back(std::pair<float, InputControl&>(weight, inputControl));
}

void InputHandler::addMouseControl(uint32 mouseButton, InputControl& inputControl, float weight)
{
	m_inputs[mouseButton + MOUSE_OFFSET].push_back(std::pair<float, InputControl&>(weight, inputControl));
}

void InputHandler::updateInput(uint32 inputCode, float dir, bool isRepeat)
{
	if (isRepeat)
		return;
	for (uint32 i = 0; i < m_inputs[inputCode].size(); i++) {
		m_inputs[inputCode][i].second.AddAmt(m_inputs[inputCode][i].first * dir);
	}
}
