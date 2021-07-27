#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace SOMA_ENGINE {
	enum class CameraMovement {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FOWARD,
		BACKWARD
	};
	struct CameraProps {
		float width;
		float height;
		float fov;
		float fov_near;
		float fov_far;
		float zoom;
		float cameraSpeed;
		float cameraSensitivity;
		/*Ortho Settings*/
		float left;
		float right;
		float top;
		float bottom;

		bool isOrthographic = false;
	};
	class Camera {
	public:
		virtual ~Camera() {};
		virtual glm::mat4 CalculateProjectionMatrix() = 0;
		virtual void Move(CameraMovement moveDirection, float deltaTime) = 0;
		virtual glm::mat4 CalculateViewMatrix() = 0;
		glm::mat4 GetProjection() { return m_projectionMatrix; }
		glm::mat4 GetView() { return m_viewMatrix; }
		glm::mat4 GetViewProjection() { return m_viewProjection; }

	protected:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjection;
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;
		glm::vec3 m_cameraRight;
		glm::vec3 m_worldUp;
		glm::vec3 m_cameraRotation;
		glm::vec3 m_cameraPosition;

		CameraProps* m_props;

	private:
		virtual void UpdateCameraVectors() = 0;
	};
}
