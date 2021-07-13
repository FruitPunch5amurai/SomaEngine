#pragma once

#include "common.hpp"
class SOMA_API IApplicationEventHandler {
public:
	IApplicationEventHandler() {}
	virtual ~IApplicationEventHandler() {}

	virtual void onKeyDown(uint32 keyCode, bool isRepeat) {}
	virtual void onKeyUp(uint32 keyCode, bool isRepeat) {}
	virtual void onMouseDown(uint32 mouseButton, uint8 numClicks) {}
	virtual void onMouseUp(uint32 mouseButton, uint8 numClicks) {}
	virtual void onMouseMove(uint32 mousePosX, uint32 mousePosY, uint32 deltaX, uint32 deltaY) {}

private:
	NULL_COPY_AND_ASSIGN(IApplicationEventHandler);

};