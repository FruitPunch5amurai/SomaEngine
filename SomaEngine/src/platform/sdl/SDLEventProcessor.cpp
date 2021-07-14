#include "somapch.hpp"

#include "platform/sdl/SDLEventProcessor.hpp"
#include "platform/generic/GenericWindow.hpp"
#include <SDL/SDL.h>
#include <core/Logger.hpp>
#include <platform/sdl/SDLWindow.hpp>
#include <events/KeyEvent.hpp>
#include <events/ApplicationEvent.hpp>
#include <events/MouseEvent.hpp>
GenericEventProcessor* GenericEventProcessor::create(GenericWindow* genericWindow)
{
	return new SDLEventProcessor((SDLWindow*)genericWindow);
}

SDLEventProcessor::SDLEventProcessor(SDLWindow* window)
{
	this->m_sdlWindow = window;
	Init();
}

SDLEventProcessor::~SDLEventProcessor()
{
	Destroy();
}

void SDLEventProcessor::processMessages(IApplicationInputHandler& eventHandler)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_WINDOWEVENT)
		{
			switch (e.window.event)
			{
				case SDL_WINDOWEVENT_RESIZED:
				{
					SOMA_ENGINE::WindowResizeEvent ev(e.window.data1, e.window.data2);
					m_sdlWindow->winData.EventCallback(ev);
					break;
				}
				case SDL_WINDOWEVENT_CLOSE:
				{
					SOMA_ENGINE::WindowCloseEvent ev;
					m_sdlWindow->winData.EventCallback(ev);
					break;
				}
				default:
					break;
			}
		}
		else {
			switch (e.type) {
			case SDL_KEYDOWN:
			{
				eventHandler.onKeyDown(e.key.keysym.scancode, e.key.repeat != 0);
				SOMA_ENGINE::KeyPressedEvent ev(e.key.keysym.scancode, 0);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}
			case SDL_KEYUP:
			{
				eventHandler.onKeyUp(e.key.keysym.scancode, e.key.repeat != 0);
				SOMA_ENGINE::KeyReleasedEvent ev(e.key.keysym.scancode);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}
			case SDL_TEXTINPUT:
			{
				SOMA_ENGINE::KeyTypedEvent ev(e.key.keysym.scancode,e.text.text);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				eventHandler.onMouseDown(e.button.type, e.button.clicks);
				SOMA_ENGINE::MouseButtonPressedEvent ev(e.button.button - 1);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				eventHandler.onMouseUp(e.button.type, e.button.clicks);
				SOMA_ENGINE::MouseButtonReleasedEvent ev(e.button.button - 1);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				eventHandler.onMouseMove(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
				SOMA_ENGINE::MouseMovedEvent ev(e.motion.x, e.motion.y);
				m_sdlWindow->winData.EventCallback(ev);
				break;
			}

			default:
				break;
			};
		}
	}
}

void SDLEventProcessor::Init()
{
	//const uint32 flags = SDL_INIT_EVERYTHING;
	//uint32 initialized = SDL_WasInit(flags);
	//if (initialized & flags) 
	//	return;
	//else{
	//	int success = SDL_Init(flags);
	//	SOMA_ASSERT(success == 0, SDL_GetError());
	//}
	running = true;
}

void SDLEventProcessor::Destroy()
{
	SDL_Quit();
}
