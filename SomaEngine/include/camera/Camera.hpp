#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace SOMA_ENGINE {
	class Camera {
	public:
		virtual ~Camera() {};
		virtual glm::mat4 CalculateProjectionMatrix() = 0;
		virtual void Move(glm::vec3 newPosition) = 0;
		virtual glm::mat4 CalculateViewMatrix() = 0;
		virtual glm::mat4 GetProjection()const = 0;
		virtual glm::mat4 GetView() const = 0;

		virtual void SetOrthoSettings(float left, float right, float top, float bottom) = 0;
		virtual void SetPerspectiveSettings(float fov,
			float fov_near,
			float fov_far,
			float width,
			float height) = 0;
	};
}
