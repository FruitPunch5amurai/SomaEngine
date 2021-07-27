#include "somapch.hpp"

#include "camera/FirstPersonCamera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "math/math.hpp"

namespace SOMA_ENGINE {
	FirstPersonCamera::FirstPersonCamera(glm::vec3 position,
		glm::vec3 rotation, CameraProps* props)
	{
		m_cameraPosition = position;
		m_cameraRotation = rotation;

		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		m_cameraPosition = position;
		m_cameraUp = m_worldUp;
		m_cameraRotation.y = rotation.y;
		m_cameraRotation.x = rotation.x;

		this->m_props = props;

		UpdateCameraVectors();
		CalculateProjectionMatrix();
		CalculateViewMatrix();
	}
	glm::mat4 FirstPersonCamera::CalculateProjectionMatrix()
	{
		if (m_props->isOrthographic)
		{
			m_projectionMatrix = glm::ortho(m_props->left, m_props->right,
				m_props->bottom, m_props->top,-1.0f,1.0f);
		}
		else {
			m_projectionMatrix = glm::perspective((float)glm::radians(m_props->fov),
				(float)m_props->width
				/ (float)m_props->height,
				m_props->fov_near, m_props->fov_far);
		}
		return m_projectionMatrix;
	}
	void FirstPersonCamera::Move(CameraMovement moveDirection,float deltaTime)
	{
		switch (moveDirection)
		{
			case CameraMovement::LEFT:
				m_cameraPosition.x -= m_props->cameraSpeed * deltaTime;
				break;
			case CameraMovement::RIGHT:
				m_cameraPosition.x += m_props->cameraSpeed * deltaTime;
				break;
			case CameraMovement::UP:
				m_cameraPosition.y += m_props->cameraSpeed * deltaTime;
				break;
			case CameraMovement::DOWN:
				m_cameraPosition.y -= m_props->cameraSpeed * deltaTime;
				break;
			case CameraMovement::FOWARD:
				m_cameraPosition.z -= m_props->cameraSpeed * deltaTime;
				break;
			case CameraMovement::BACKWARD:
				m_cameraPosition.z += m_props->cameraSpeed * deltaTime;
				break;
		}
		CalculateViewMatrix();
	}
	glm::mat4 FirstPersonCamera::CalculateViewMatrix()
	{
		if (m_props->isOrthographic){
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_cameraPosition.x,m_cameraPosition.y,0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraRotation.z), glm::vec3(0, 0, 1));
			m_viewMatrix = glm::inverse(transform);
		}
		else {
			m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
		}
		return m_viewMatrix;
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