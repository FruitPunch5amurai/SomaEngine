#pragma once

#include "common.hpp"
class  IApplicationInputHandler {
public:
	IApplicationInputHandler() {}
	virtual ~IApplicationInputHandler() {}

	virtual void onKeyDown(uint32 keyCode, bool isRepeat) {}
	virtual void onKeyUp(uint32 keyCode, bool isRepeat) {}
	virtual void onMouseDown(uint32 mouseButton, uint8 numClicks) {}
	virtual void onMouseUp(uint32 mouseButton, uint8 numClicks) {}
	virtual void onMouseMove(uint32 mousePosX, uint32 mousePosY, uint32 deltaX, uint32 deltaY) {}

private:

};