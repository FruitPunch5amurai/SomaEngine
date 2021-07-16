#pragma once

#include "core/common.hpp"
#include "core/IApplicationInputHandler.hpp"
#include "InputControl.hpp"


class  InputHandler : public IApplicationInputHandler {
public:
	InputHandler() {}
	virtual ~InputHandler() {}

	virtual void onKeyDown(uint32 keyCode, bool isRepeat);
	virtual void onKeyUp(uint32 keyCode, bool isRepeat);
	virtual void onMouseDown(uint32 mouseButton, uint8 numClicks);
	virtual void onMouseUp(uint32 mouseButton, uint8 numClicks);
	virtual void onMouseMove(uint32 mousePosX, uint32 mousePosY, uint32 deltaX, uint32 deltaY);

	void addKeyControl(uint32 keyCode, InputControl& inputControl,float weight = 1.0f);
	void addMouseControl(uint32 mouseButton, InputControl& inputControl, float weight = 1.0f);

private:
	Map<uint32, SOMA_Array<std::pair<float, InputControl&>>> m_inputs;
	void updateInput(uint32 inputCode, float dir, bool isRepeat);

};