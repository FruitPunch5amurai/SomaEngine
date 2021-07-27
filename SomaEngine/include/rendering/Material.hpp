#pragma once



#include <GLM/glm.hpp>
#include "core/common.hpp"
/*TODO: Get rid of this*/
struct MaterialSpec
{
	Map<SOMA_String, SOMA_String> textureNames;
	Map<SOMA_String, uint32> ids;
	Map<SOMA_String, float> floats;
	Map<SOMA_String, glm::vec3> vectors;
	Map<SOMA_String, glm::mat4> matrices;
};

namespace SOMA_ENGINE {
	struct MaterialSpec
	{
		//Map<SOMA_String, SOMA_String> textureNames;
		//Map<SOMA_String, uint32> ids;
		//Map<SOMA_String, float> floats;
		//Map<SOMA_String, glm::vec3> vectors;
		//Map<SOMA_String, glm::mat4> matrices;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		uint32 shininess;
	};
}