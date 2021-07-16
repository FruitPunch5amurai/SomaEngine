#pragma once

#include "common.hpp"
#include "events/Event.hpp"

namespace SOMA_ENGINE {
	class  Layer {
	public:
		Layer(const SOMA_String& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const SOMA_String& GetName() const { return m_name; }
	protected:
		SOMA_String m_name;
	};
}