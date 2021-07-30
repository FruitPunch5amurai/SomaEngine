#pragma once
#include "camera/Camera.hpp"
#include "events/MouseEvent.hpp"
#include "events/ApplicationEvent.hpp"
#include <camera/FirstPersonCamera.hpp>

namespace SOMA_ENGINE {
	class CameraController {
	public:
		CameraController(glm::vec3 position, glm::vec3 rotation, float width, float height);

		void OnUpdate(float timestep);
		void OnEvent(Event& e);
		void SetOrthographic(float left, float right, float top, float bottom);
		void SetPerspective(float fov,float fov_near,float fov_far,float width,float height);
		void EnableOrthographic(bool b);

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		Ref<Camera> GetCamera() { return m_camera; }
		const Ref<Camera> GetCamera()const { return m_camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		Ref<Camera> m_camera;

		glm::vec3 m_cameraPosition;
		glm::vec3 m_cameraRotation;

		float m_fov,m_fov_near,m_fov_far,m_width,m_height;
		float m_zoom = 45.0f;
		float m_cameraSpeed;

	};
}