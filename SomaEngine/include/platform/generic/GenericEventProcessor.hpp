#pragma once
#include "core/common.hpp"
#include "core/IApplicationInputHandler.hpp"
#include "platform/generic/GenericWindow.hpp"

class  GenericEventProcessor {
public:
	virtual ~GenericEventProcessor() {}
	virtual void processMessages() = 0;
	inline bool isRunning() const { return running; }

	static GenericEventProcessor* create(GenericWindow* genericWindow);
protected:
	bool running;
};