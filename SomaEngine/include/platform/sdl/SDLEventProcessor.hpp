#pragma once
#include "platform/generic/GenericEventProcessor.hpp"
#include "platform/sdl/SDLWindow.hpp"
class SOMA_API SDLEventProcessor : public GenericEventProcessor {
public:
	SDLEventProcessor(SDLWindow* genericWindow);
	virtual ~SDLEventProcessor();
	void processMessages(IApplicationInputHandler& eventHandler) override;


private:
	virtual void Init();
	virtual void Destroy();
	
	SDLWindow* m_sdlWindow;

};