#pragma once



#include <GLM/glm.hpp>

struct MaterialSpec
{
	Map<SOMA_String, SOMA_String> textureNames;
	Map<SOMA_String, uint32> ids;
	//Map<String, float> floats;
	//Map<String, glm::vec3> vectors;
	//Map<String, glm::mat4> matrices;
};