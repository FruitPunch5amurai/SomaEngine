#pragma once
#include "core/common.hpp"
#include "core/IApplicationEventHandler.hpp"
#include "platform/generic/GenericWindow.hpp"

class SOMA_API GenericEventProcessor {
public:
	virtual ~GenericEventProcessor() {}
	virtual void processMessages(IApplicationEventHandler& eventHandler) = 0;
	inline bool isRunning() const { return running; }

	static GenericEventProcessor* create(GenericWindow* genericWindow);
protected:
	bool running;
};