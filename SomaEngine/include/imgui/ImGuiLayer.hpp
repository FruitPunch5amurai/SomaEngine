#pragma once
#include "core/Layer.hpp"
#include "events/Event.hpp"

namespace SOMA_ENGINE {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);
	private:
	};
}