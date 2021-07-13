#include "somapch.hpp"

#include "platform/sdl/SDLWindow.hpp"
#include "rendering/RenderDevice.hpp"
#include <stdexcept>
#include <core/Logger.hpp>
#include <glad/glad.h>
#include <platform/opengl/OpenGLRenderDevice.hpp>

GenericWindow* GenericWindow::create(const WindowProps& props)
{
	return new SDLWindow(props);
}


SDLWindow::SDLWindow(const WindowProps& props)
{
	Init(props);
}
void SDLWindow::Init(const WindowProps& props)
{
	const uint32 flags = SDL_INIT_EVERYTHING;
	uint32 initialized = SDL_WasInit(flags);
	if (initialized & flags)
		return;
	else {
		int success = SDL_Init(flags);
		SOMA_ASSERT(success == 0, SDL_GetError());
	}

	winData.width = props.width;
	winData.height = props.height;
	winData.title = props.title;
	bool success = RenderDevice::globalInit();

	SOMA_ASSERT(success, "SDL Window could not be initialized ");

	SDL_GL_LoadLibrary(NULL);

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SOMA_CORE_DEBUG("SDL Window Created: {0} ({1},{2})",props.title, props.width, props.height);

	window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, props.width, props.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	windowHandle = window;

	DeviceContext maincontext = SDL_GL_CreateContext(window);
}
void SDLWindow::Destroy()
{
	SDL_DestroyWindow(window);
}
SDLWindow::~SDLWindow()
{
	Destroy();
}

void SDLWindow::update()
{
	SDL_GL_SwapWindow(window);
}


