#pragma once
#include "camera/Camera.hpp"

namespace SOMA_ENGINE {
	class FirstPersonCamera : public Camera
	{
	public:
		FirstPersonCamera(glm::vec3 position, glm::vec3 rotation,
			CameraProps* props);
		~FirstPersonCamera() {}
		virtual glm::mat4 CalculateProjectionMatrix()  override;
		virtual void Move(CameraMovement moveDirection)  override;
		virtual glm::mat4 CalculateViewMatrix()  override;
	private:
		virtual void UpdateCameraVectors() override;
	};
}