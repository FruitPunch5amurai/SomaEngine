#include "somapch.hpp"

#include "camera/CameraController.hpp"
#include "input/Input.hpp"
#include "core/common.hpp"
#include "core/Logger.hpp"
namespace SOMA_ENGINE {
	CameraController::CameraController(glm::vec3 position,glm::vec3 rotation,float width,float height)		
	{
		m_cameraPosition = position;
		m_cameraRotation = rotation;
		m_camera = CreateRef<FirstPersonCamera>(position, rotation);
		EnableOrthographic(false);
		SetPerspective(45.0f,0.1f,1000.0f,width,height);
		m_cameraSpeed = 1.5f;
	}
	void CameraController::OnUpdate(float timestep)
	{
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::D)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x + (m_cameraSpeed * timestep), m_cameraPosition.y, m_cameraPosition.z);
		}
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::A)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x - (m_cameraSpeed * timestep), m_cameraPosition.y, m_cameraPosition.z);
		}
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::E)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x, m_cameraPosition.y + (m_cameraSpeed * timestep), m_cameraPosition.z);
		}
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::Q)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x, m_cameraPosition.y - (m_cameraSpeed * timestep), m_cameraPosition.z);
		}
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::W)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z - (m_cameraSpeed * timestep));
		}
		if (Input::IsKeyPressed(SOMA_ENGINE::Key::S)) {
			m_cameraPosition = glm::vec3(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z + (m_cameraSpeed * timestep));
		}

		m_camera->Move(m_cameraPosition);
		m_cameraSpeed = m_zoom;
	}
	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(SOMA_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SOMA_BIND_EVENT_FN(CameraController::OnWindowResized));
	}
	void CameraController::SetOrthographic(float left, float right, float top, float bottom)
	{
	}
	void CameraController::SetPerspective(float fov, float fov_near, float fov_far, float width, float height)
	{
		m_fov = fov;
		m_fov_near = fov_near;
		m_fov_far = fov_far;
		m_width = width;
		m_height = height;

		m_camera->SetPerspectiveSettings(fov, fov_near, fov_far, width, height);
	}
	void CameraController::EnableOrthographic(bool b)
	{
	}
	glm::mat4 CameraController::GetViewMatrix()
	{
		return m_camera->GetView();
	}
	glm::mat4 CameraController::GetProjectionMatrix()
	{
		return m_camera->GetProjection();
	}
	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_zoom += e.GetYOffset() * 0.25f;

		SetPerspective(m_zoom, m_fov_near, m_fov_far, m_width, m_height);
		return false;
	}
	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		//m_width = e.GetWidth();
		//m_height = e.GetHeight();
		//SetPerspective(m_zoom, m_fov_near, m_fov_far, m_width, m_height);
		return false;
	}
}