#pragma once

#include "rendering/IndexedModel.hpp"
#include "rendering/Material.hpp"
#include <rendering/Model.hpp>

namespace ModelLoader
{
	Model* loadModels(const SOMA_String& fileName);
}