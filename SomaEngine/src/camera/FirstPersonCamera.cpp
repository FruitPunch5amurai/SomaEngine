#include "somapch.hpp"

#include "camera/FirstPersonCamera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "math/math.hpp"
#include "core/Logger.hpp"

namespace SOMA_ENGINE {
	FirstPersonCamera::FirstPersonCamera(glm::vec3 position,
		glm::vec3 rotation)
	{
		m_cameraPosition = position;
		m_cameraRotation = rotation;

		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_cameraPosition = position;
		m_cameraUp = m_worldUp;
		m_cameraRotation.y = rotation.y;
		m_cameraRotation.x = rotation.x;

		UpdateCameraVectors();
		CalculateProjectionMatrix();
		CalculateViewMatrix();
	}
	glm::mat4 FirstPersonCamera::CalculateProjectionMatrix()
	{
		if (m_isOrtho)
		{
			m_projectionMatrix = glm::ortho(m_left, m_right,
				m_bottom, m_top,-1.0f,1.0f);
		}
		else {
			m_projectionMatrix = glm::perspective((float)glm::radians(m_fov),
				(float)m_width
				/ (float)m_height,
				m_fov_near, m_fov_far);
		}
		return m_projectionMatrix;
	}
	void FirstPersonCamera::Move(glm::vec3 newPosition)
	{
		m_cameraPosition = newPosition;

		CalculateViewMatrix();
	}
	glm::mat4 FirstPersonCamera::CalculateViewMatrix()
	{
		if (m_isOrtho){
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_cameraPosition.x,m_cameraPosition.y,0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraRotation.z), glm::vec3(0, 0, 1));
			m_viewMatrix = glm::inverse(transform);
		}
		else {
			m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
		}
		return m_viewMatrix;
	}
	void FirstPersonCamera::SetPerspectiveSettings(float fov, float fov_near, float fov_far, float width, float height)
	{
		m_fov = fov; m_fov_near = fov_near; m_fov_far = fov_far; m_width = width; m_height = height;
		CalculateProjectionMatrix();
	}
	void FirstPersonCamera::UpdateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = Math::cos(Math::toRadians(m_cameraRotation.y)) * Math::cos(Math::toRadians(m_cameraRotation.x));
		front.y = Math::sin(Math::toRadians(m_cameraRotation.x));
		front.z = Math::sin(Math::toRadians(m_cameraRotation.y)) * Math::cos(Math::toRadians(m_cameraRotation.x));
		m_cameraFront = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
	}
}