#pragma once
#include "camera/Camera.hpp"

namespace SOMA_ENGINE {
	class FirstPersonCamera : public Camera
	{
	public:
		FirstPersonCamera(glm::vec3 position,glm::vec3 rotation);
		~FirstPersonCamera() {}
		virtual glm::mat4 CalculateProjectionMatrix()  override;
		virtual void Move(glm::vec3 newPosition)  override;
		virtual glm::mat4 CalculateViewMatrix()  override;
		virtual glm::mat4 GetProjection() const { return m_projectionMatrix; }
		virtual glm::mat4 GetView() const { return m_viewMatrix; };

		void EnableOrtho() { m_isOrtho = true; }
		void DisableOrtho() { m_isOrtho = false; }

		void SetOrthoSettings(float left, float right, float top, float bottom) override { m_left = left; m_right = right; m_top = top; m_bottom = bottom; };
		void SetPerspectiveSettings(float fov,
			float fov_near,
			float fov_far,
			float width,
			float height) override;
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjection;
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;
		glm::vec3 m_cameraRight;
		glm::vec3 m_worldUp;
		glm::vec3 m_cameraRotation;
		glm::vec3 m_cameraPosition;

		/*Ortho Settings*/
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;
		bool m_isOrtho = false;

		/*Perspective Settings*/
		float m_fov;
		float m_fov_near;
		float m_fov_far;
		float m_width;
		float m_height;

		void UpdateCameraVectors();
	};
}