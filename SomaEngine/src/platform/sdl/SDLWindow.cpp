#include "somapch.hpp"

#include "platform/sdl/SDLWindow.hpp"
#include "rendering/RenderDevice.hpp"
#include <stdexcept>
#include <core/Logger.hpp>
#ifdef SOMA_RENDER_OPENGL
#include <glad/glad.h>
#include <platform/opengl/OpenGLRenderDevice.hpp>
#endif
GenericWindow* GenericWindow::create(const WindowProps& props)
{
	return new SDLWindow(props);
}


SDLWindow::SDLWindow(const WindowProps& props)
{
	Init(props);
}

bool SDLWindow::IsKeyPressed(uint32 key) const
{
	return m_inputManager.isKeyDown(key);
}

bool SDLWindow::IsMouseButtonPressed(uint32 key) const
{
	return m_inputManager.isKeyDown(key);
}

glm::vec2 SDLWindow::GetMousePosition() const
{
	return m_inputManager.getMouseCoords();
}

void SDLWindow::KeyPress(uint32 keyId)
{
	m_inputManager.KeyPress(keyId);
}

void SDLWindow::KeyRelease(uint32 keyId)
{
	m_inputManager.KeyRelease(keyId);
}

void SDLWindow::SetMouseCoords(float x, float y)
{
	m_inputManager.setMouseCoords(x, y);
}

void SDLWindow::UpdateInput()
{
	m_inputManager.Update();
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

	window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, props.width, props.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	windowHandle = window;
#ifdef SOMA_RENDER_OPENGL
	SDL_GL_LoadLibrary(NULL);
	// Request an OpenGL 4.5 context (should be core)
	const char* glsl_version = "#version 410";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SOMA_CORE_DEBUG("SDL Window Created: {0} ({1},{2})",props.title, props.width, props.height);

	m_context = SDL_GL_CreateContext(window);
	context = m_context;
	SDL_GL_MakeCurrent(window, m_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SOMA_CORE_ERROR("Failed to initialize the OpenGL context");
	}
	SOMA_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Soma requires at least OpenGL version 4.5!");

	SOMA_CORE_DEBUG("OpenGL Info: ");
	SOMA_CORE_DEBUG("---Vendor:{0}", glGetString(GL_VENDOR));
	SOMA_CORE_DEBUG("---Renderer:{0}", glGetString(GL_RENDERER));
	SOMA_CORE_DEBUG("---Version:{0}", glGetString(GL_VERSION));
#endif
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
#ifdef SOMA_RENDER_OPENGL
	SDL_GL_SwapWindow(window);
#endif
}



