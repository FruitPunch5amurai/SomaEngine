#pragma once
#include <SDL/SDL.h>

#include "core/Layer.hpp"
#include "events/Event.hpp"
#include "events/KeyEvent.hpp"
#include "events/MouseEvent.hpp"
#include "events/ApplicationEvent.hpp"
namespace SOMA_ENGINE {
	class SOMA_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


		float m_time = 0.0f;
		SDL_Cursor* g_MouseCursors[9] = {};
	};
}