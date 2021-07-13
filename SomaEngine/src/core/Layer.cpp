#include "somapch.hpp"

#include "core/Layer.hpp"

namespace SOMA_ENGINE {
	Layer::Layer(const SOMA_String& name)
	{
		m_name = name;
	}
	Layer::~Layer()
	{
	}
}